//------PCH-----------------------------------------------------------------
#include "VttApiPch.h"
//--------------------------------------------------------------------------


#include "Network/Socket/UdpSocket.h"

namespace Virtual_Tt_Api {

	UdpSocket::UdpSocket() {}

	UdpSocket::~UdpSocket() {}

	bool UdpSocket::Socket_Bind() {

		if (!bind(socket_handle,
			rp->ai_addr,
			rp->ai_addrlen)) {

			#ifdef VTT_PLATFORM_WINDOWS
			VTT_API_ERROR("Error binding to address and port: {1}",
				(void*)WSAGetLastError);
			#elif VTT_PLATFORM_LINUX
			VTT_API_ERROR("Error binding to address and port: {1}",
				(void*)gai_strerror);
			#endif
			
			return false;
		}

		// Print the IP address and port the socket is now bound to.
		char addr_buffer[128];
		size_t addr_buffer_len = sizeof(addr_buffer);
		if (rp->ai_addr->sa_family == AF_INET) {

			struct sockaddr_in sin;
			socklen_t sin_len = sizeof(sin);
			if (getsockname(socket_handle,
				(struct sockaddr*)&sin,
				&sin_len) == 0) {
				
				inet_ntop(AF_INET,
					&(sin.sin_addr),
					addr_buffer,
					addr_buffer_len);
				u_short port = ntohs(sin.sin_port);

				VTT_API_INFO("Socket bound to IP address {1} and port {2}",
					addr_buffer,
					port);

				// Fill in the HostInformation.
				host_info = HostInformation(&sin,
					port);
			}
		}
		else if (rp->ai_addr->sa_family == AF_INET6) {
		
			struct sockaddr_in6 sin6;
			socklen_t sin6_len = sizeof(sin6);
			if (getsockname(socket_handle,
				(struct sockaddr*)&sin6,
				&sin6_len) == 0) {

				inet_ntop(AF_INET6,
					&(sin6.sin6_addr),
					addr_buffer,
					addr_buffer_len);
				u_short port = ntohs(sin6.sin6_port);

				VTT_API_INFO("Socket bound to IP address {1} and port {2}",
					addr_buffer,
					port);

				// Fill in the HostInformation.
				host_info = HostInformation(&sin6,
					port);
			}
		}

		// Free up the addrinfo structs because they're no longer needed.
		freeaddrinfo(result);
		freeaddrinfo(rp);

		// Put the socket into non-blocking mode.
		#ifdef VTT_PLATFORM_WINDOWS
		unsigned long nonblocking = 1;
		if (ioctlsocket(socket_handle,
			FIONBIO,
			&nonblocking) != 0) {

			VTT_API_ERROR("Error setting the socket to non-blocking: {1}",
				(void*)WSAGetLastError);
			return false;
		}
		#elif VTT_PLATFORM_LINUX
		int blocking = 1;
		if (fcntl(socket_handle,
			F_SETFL,
			O_NONBLOCK,
			nonblocking) == -1) {

			VTT_API_ERROR("Error setting the socket to non-blocking: {1}",
				(void*)gai_strerror);
			return false;
		}
		#endif // VTT_PLATFORM_WINDOWS

		// Update the SocketState to BOUND to indicate that the socket has been 
		// bound to an IP address and a port.
		socket_state = SocketState::BOUND;

		return true;
	}

	bool UdpSocket::Socket_Close() {

		#ifdef VTT_PLATFORM_WINDOWS
		closesocket(socket_handle);
		#elif VTT_PLATFORM_LINUX
		close(socket_handle);
		#endif // VTT_PLATFORM_WINDOWS

		// Update the SocketState to CLOSING to indicate that the socket is closing.
		socket_state = SocketState::CLOSING;

		return true;
	}

	bool UdpSocket::Socket_Create(int addr_info_family, 
		int addr_info_flag) {

		// addrinfo struct
		struct addrinfo hints;

		// Resolve address and port.
		memset(&hints, NULL, sizeof(addrinfo));
		hints.ai_family = addr_info_family;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;
		hints.ai_flags = addr_info_flag;

		char host_name[32];
		int host = gethostname(host_name,
			sizeof(host_name));

		// Get address information on any free port using the host name.
		int address_info = getaddrinfo(host_name,
			NULL,
			&hints,
			&result);
		if (address_info != 0) {

			#ifdef VTT_PLATFORM_WINDOWS
			VTT_API_ERROR("Failed to resolve address info. Error: {1}",
				(void*)WSAGetLastError);
			#elif VTT_PLATFORM_LINUX
			VTT_API_ERROR("Failed to resolve address info. Error: {1}",
				(void*)gai_strerror);
			#endif // VTT_PLATFORM_WINDOWS

			return false;
		}

		// Iterate through the returned address info struct and initialise the socket.
		for (rp = result; rp != NULL; rp->ai_next) {

			// If the item pointed at by rp->ai_next is NULL return false.
			if (rp->ai_next == NULL) {

				VTT_API_ERROR("Failed to create a socket.");

				return false;
			}

			// Get the socket handle for the IP family, socket type and IP protocol.
			socket_handle = socket(rp->ai_family,
				rp->ai_socktype,
				rp->ai_protocol);

			#ifdef VTT_PLATFORM_WINDOWS
			if (socket_handle == INVALID_SOCKET) {

				continue;
			}
			#elif VTT_PLATFORM_LINUX
			if (socket_handle == -1) {

				continue;
			}
			#endif // VTT_PLATFORM_WINDOWS
			else {

				break;
			}

			// If the initialisation fails close the socket file descriptor.
			Socket_Close();
		}

		// Update the SocketState to DISCONNECTED to indicate that the socket
		// was created but is not yet bound.
		socket_state = SocketState::DISCONNECTED;
		
		return true;
	}
	
	bool UdpSocket::Socket_Create(int addr_info_family,
		int addr_info_flag,
		std::string ip_address) {

		// addrinfo structs.
		struct addrinfo hints;

		// Resolve address and port
		memset(&hints, NULL, sizeof(addrinfo));
		hints.ai_family = addr_info_family;
		hints.ai_socktype = SOCK_DGRAM;
		hints.ai_protocol = IPPROTO_UDP;
		hints.ai_flags = addr_info_flag;

		// Get the address info of the external IP address on any free port.
		int address_info = getaddrinfo(ip_address.c_str(),
			NULL,
			&hints,
			&result);
		if (address_info != 0) {

			#ifdef VTT_PLATFORM_WINDOWS
			VTT_API_ERROR("Failed to resolve address info. Error: {1}", 
				(void*)WSAGetLastError);
			#elif VTT_PLATFORM_LINUX
			VTT_API_ERROR("Failed to resolve address info. Error: {1}", 
				(void*)gai_strerror);
			#endif // VTT_PLATFORM_WINDOWS

			return false;
		}

		// Iterate through the returned address info struct and initialise the socket.
		for (rp = result; rp != NULL; rp->ai_next) {

			// If the item pointed at by rp->ai_next is NULL return false.
			if (rp->ai_next == NULL) {

				VTT_API_ERROR("Failed to create a socket with the entered address.");

				return false;
			}

			// Get the socket handle for the IP family, socket type and IP protocol.
			socket_handle = socket(rp->ai_family,
				rp->ai_socktype,
				rp->ai_protocol);

			#ifdef VTT_PLATFORM_WINDOWS
			if (socket_handle == INVALID_SOCKET) {

				continue;
			}
			#elif VTT_PLATFORM_LINUX
			if (socket_handle == -1) {

				continue;
			}
			#endif // VTT_PLATFORM_WINDOWS
			else {
			
				break;
			}

			// If the initialisation fails close the socket file descriptor.
			Socket_Close();
		}

		// Update the SocketState to DISCONNECTED to indicate that the socket
		// was created but is not yet bound.
		socket_state = SocketState::DISCONNECTED;

		return true;
	}

	// Initialise the socket layer on Windows.
	bool UdpSocket::Socket_Initialise() {
	
		#ifdef VTT_PLATFORM_WINDOWS
		WSADATA wsa_data;
		return WSAStartup(MAKEWORD(2, 2), &wsa_data);
		#else
		return true;
		#endif // VTT_PLATFORM
	}

	int UdpSocket::Socket_Receive(HostInformation& sender_socket,
		void* data,
		int data_size) {

		if (host_info.ip_family == IpFamily::IP_V4) {

			#if VTT_PLATFORM_WINDOWS
			typedef int socklen_t;
			#endif // VTT_PLATFORM_WINDOWS

			sockaddr_in sender_info;
			socklen_t sender_length = sizeof(sender_info);

			int bytes_read = recvfrom(socket_handle,
				(char*)data,
				data_size,
				0,
				(sockaddr*)&sender_info,
				&sender_length);

			sender_socket = HostInformation(&sender_info,
				ntohs(sender_info.sin_port));

			return bytes_read;
		}
		else if (host_info.ip_family == IpFamily::IP_V6) {

			#if VTT_PLATFORM_WINDOWS
			typedef int socklen_t;
			#endif // VTT_PLATFORM_WINDOWS

			sockaddr_in6 sender_info;
			socklen_t sender_length = sizeof(sender_info);

			int bytes_read = recvfrom(socket_handle,
				(char*)data,
				data_size,
				0,
				(sockaddr*)&sender_info,
				&sender_length);

			sender_socket = HostInformation(&sender_info,
				ntohs(sender_info.sin6_port));

			return bytes_read;
		}
	}

	bool UdpSocket::Socket_Send(const HostInformation& destination,
		const void* packet_data,
		int packet_size) {

		if (destination.ip_family == IpFamily::IP_V4) {

			sockaddr_in destination_address;
			destination_address.sin_family = AF_INET;
			destination_address.sin_addr.S_un.S_addr = destination.network_address.ip_v4_address.address;
			destination_address.sin_port = destination.network_port;
			#if VTT_PLATFORM_WINDOWS
			typedef int socklen_t;
			#endif // VTT_PLATFORM_WINDOWS
			socklen_t destination_length = sizeof(destination_address);

			int bytes_sent = sendto(socket_handle,
				(char*)packet_data,
				packet_size,
				0,
				(sockaddr*)&destination_address,
				destination_length);

			if (bytes_sent != packet_size) {

				VTT_API_ERROR("Failed to send package!");
				return false;
			}

			return true;
		}
		else if (destination.ip_family == IpFamily::IP_V6) {

			sockaddr_in6 destination_address;
			destination_address.sin6_family = AF_INET6;
			for (int i = 0; i < 8; i++) {

				destination_address.sin6_addr.u.Word[i] = destination.network_address.ip_v6_address.a[i];
			}
			destination_address.sin6_port = destination.network_port;
			#if VTT_PLATFORM_WINDOWS
			typedef int socklen_t;
			#endif // VTT_PLATFORM_WINDOWS
			socklen_t destination_length = sizeof(destination_address);

			int bytes_sent = sendto(socket_handle,
				(char*)packet_data,
				packet_size,
				0,
				(sockaddr*)&destination_address,
				destination_length);

			if (bytes_sent != packet_size) {

				VTT_API_ERROR("Failed to send package!");
				return false;
			}

			return true;
		}
		else {

			VTT_API_ERROR("Invalid HostInformation!");
			return false;
		}
	}

	// Clean up the socket layer on Windows.
	void UdpSocket::Socket_Shutdown() {

		#ifdef VTT_PLATFORM_WINDOWS
		WSACleanup();
		#endif // VTT_PLATFORM_WINDOWS
	}
}