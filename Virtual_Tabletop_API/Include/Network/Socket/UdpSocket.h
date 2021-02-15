#pragma once
#ifndef UDPSOCKET_H
#define UDPSOCKET_H

#include "Network/Socket/NetworkSocket.h"

namespace Virtual_Tt_Api {

	class UdpSocket : public Virtual_Tt_Api::NetworkSocket {
	
	public:
		//Constructor & destructor
		UdpSocket();
		~UdpSocket();

		// Virtual functions
		bool Socket_Bind();
		virtual bool Socket_Close() override;
		virtual bool Socket_Create(int addr_info_family, 
			int addr_info_flag) override;
		virtual bool Socket_Create(int addr_info_family,
			int addr_info_flag,
			std::string ip_address) override;
		virtual bool Socket_Initialise() override;
		virtual int Socket_Receive(HostInformation& sender_socket,
			void* data,
			int data_size) override;
		virtual bool Socket_Send(const HostInformation& destination,
			const void* data,
			int size) override;
		virtual void Socket_Shutdown() override;

		struct addrinfo* result, * rp;
		int socket_handle = 0;
		HostInformation host_info;
		SocketState socket_state = SocketState::None;
	};
}

#endif // !UDPSOCKET_H

