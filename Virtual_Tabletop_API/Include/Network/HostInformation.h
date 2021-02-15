#pragma once
#ifndef HOSTINFORMATION_H
#define HOSTINFORMATION_H

//------PCH------
#include "VttApiPch.h"
//---------------

namespace Virtual_Tt_Api {

	enum IpFamily {

		UNSPECIFIED = AF_UNSPEC,
		IP_V4 = AF_INET,
		IP_V6 = AF_INET6
	};

	// Struct containing an IPv4 address in network byte order (big endian).
	struct Ip_V4 {
		int address;
	};
	// Struct containing an IPv6 address in network byte order (big endian).
	struct Ip_V6 {

		unsigned char a[16];
	};

	struct HostInformation {

	public:
		// Default constructor
		HostInformation() {}
		// Copy constructor
		HostInformation(const HostInformation& info) {

			ip_family = info.ip_family;
			network_address = info.network_address;
			network_port = info.network_port;
			ip_address_string = info.ip_address_string;
		}
		// Take an ip_v4 struct and store it together with the passed port.
		HostInformation(Ip_V4 address,
			u_short port) {

			network_address.ip_v4_address = address;
			network_port = htons(port);

			// Set the ip_family.
			ip_family = Virtual_Tt_Api::IpFamily::IP_V4;
			// Fill in the ip_address_string.
			char buffer[INET_ADDRSTRLEN];
			sockaddr_in addr;
			addr.sin_family = AF_INET;
			#ifdef VTT_PLATFORM_WINDOWS
			addr.sin_addr.S_un.S_addr = address.address;
			#elif	VTT_PLATFORM_LINUX
			addr.sin_addr.s_addr = address.address;
			#endif // VTT_PLATFORM_WINDWOS
			if (inet_ntop(AF_INET,
				&(addr.sin_addr),
				buffer,
				INET_ADDRSTRLEN) == NULL) {

				VTT_API_ERROR("Invalid Ip_V4 struct!");
				return;
			}
			else {

				ip_address_string.clear();
				ip_address_string.append(buffer);
			}
		}
		// Take an ip_v6 struct and store it together with the passed port.
		HostInformation(Ip_V6 address,
			u_short port) {

			for (int i = 0; i < 16; i++) {

				network_address.ip_v6_address.a[i] = address.a[i];
			}
			network_port = htons(port);

			// Set the ip_family.
			ip_family = Virtual_Tt_Api::IpFamily::IP_V6;
			// Fill in the ip_address_string.
			char buffer[INET6_ADDRSTRLEN];
			sockaddr_in6 addr;
			addr.sin6_family = AF_INET6;
			#ifdef VTT_PLATFORM_WINDOWS
			for (int i = 0; i < 16; i++) {

				addr.sin6_addr.u.Byte[i] = address.a[i];
			}
			#elif VTT_PLATFORM_LINUX
			for (int i = 0; i < 16; i++) {

				addr.sin6_addr.s6_address[i] = address.a[i];
			}
			#endif // VTT_PLATFORM_WINDOWS
			if (inet_ntop(AF_INET6,
				&(addr.sin6_addr),
				buffer,
				INET6_ADDRSTRLEN) == NULL) {

				VTT_API_ERROR("Invalid Ip_V6 struct!");
				return;
			}
			else {

				ip_address_string.clear();
				ip_address_string.append(buffer);
			}

		}
		// Take a string in host byte order (little endian) and 
		// store it in network_address together with the 
		// passed port in host byte order (little endian).
		HostInformation(std::string address,
			u_short port) {

			sockaddr_in addr;
			sockaddr_in6 addr_6;
			// Check the IpFamily value
			if (inet_pton(AF_INET,
				address.c_str(),
				&addr) == 1) {

				#ifdef VTT_PLATFORM_WINDOWS
				network_address.ip_v4_address.address = addr.sin_addr.S_un.S_addr;
				#elif VTT_PLATFORM_LINUX
				network_address.ip_v4_address.address = addr.sin_addr.s_addr;
				#endif // VTT_PLATFORM_WINDOWS

				
				// Set the ip_family.
				ip_family = Virtual_Tt_Api::IpFamily::IP_V4;
				// Fill in the ip_address_string.
				ip_address_string.clear();
				ip_address_string.append(address);
			}
			// If the address string is of the IPv6 family in the Ip_V6 struct.
			else if (inet_pton(AF_INET6,
				address.c_str(),
				&addr_6) == 1) {

				// Assign the byte values from address to network_address.ip_v6_address.
				#ifdef VTT_PLATFORM_WINDOWS
				for (int i = 0; i < 16; i++) {

					network_address.ip_v6_address.a[i] = addr_6.sin6_addr.u.Byte[i];
				}
				#elif VTT_PLATFORM_LINUX
				for (int i = 0; i < 16; i++) {

					network_address.ip_v6_address.a[i] = addr_6.sin6_addr.s6_addr[i];
				}
				#endif // VTT_PLATFORM_WINDOWS

				
				// Set the ip_family.
				ip_family = Virtual_Tt_Api::IpFamily::IP_V6;
				// Fill in the ip_address_string.
				ip_address_string.clear();
				ip_address_string.append(address);
			}
			// Else print an error message and return.
			else {

				VTT_API_ERROR("Invalid String!");
				return;
			}

			// Assign the port to network_port.
			network_port = htons(port);
		}
		HostInformation(sockaddr_in* address,
			u_short port) {

			// Assign the int value from address.sin_address to network_address.ip_v4_address.address.
			#ifdef VTT_PLATFORM_WINDOWS
			network_address.ip_v4_address.address = address->sin_addr.S_un.S_addr;
			#elif VTT_PLATFORM_LINUX
			network_address.ip_v4_address.address = address->sin_addr.s_addr;
			#endif // VTT_PLATFORM_WINDOWS

			// Assign port to network_port.
			network_port = htons(port);
			// Set the ip_family.
			ip_family = Virtual_Tt_Api::IpFamily::IP_V4;
			// Fill in the ip_address_string.
			char buffer[INET_ADDRSTRLEN];
			if (inet_ntop(AF_INET,
				&(address->sin_addr),
				buffer,
				INET_ADDRSTRLEN) == NULL) {

				VTT_API_ERROR("Invalid sockaddr_in struct!");
				return;
			}
			else {

				ip_address_string.clear();
				ip_address_string.append(buffer);
			}
		}
		HostInformation(sockaddr_in6* address,
			u_short port) {

			// Assign the byte values from address to network_address.ip_v6_address.
			#ifdef VTT_PLATFORM_WINDOWS
			for (int i = 0; i < 16; i++) {

				network_address.ip_v6_address.a[i] = address->sin6_addr.u.Byte[i];
			}
			#elif VTT_PLATFORM_LINUX
			for (int i = 0; i < 16; i++) {

				network_address.ip_v6_address.a[i] = address->sin6_addr.s6_addr[i];
			}
			#endif // VTT_PLATFORM_WINDOWS

			// Assign port to network_port.
			network_port = htons(port);
			// Set the ip_family.
			ip_family = Virtual_Tt_Api::IpFamily::IP_V6;
			// Fill in the ip_address_string.
			char buffer[INET6_ADDRSTRLEN];
			if (inet_ntop(AF_INET6,
				&(address->sin6_addr),
				buffer,
				INET6_ADDRSTRLEN) == NULL) {

				VTT_API_ERROR("Invalid sockaddr_in6 struct!");
				return;
			}
			else {

				ip_address_string.clear();
				ip_address_string.append(buffer);
			}
		}
		~HostInformation() {}

		Virtual_Tt_Api::IpFamily ip_family = IpFamily::UNSPECIFIED;
		union {
			Ip_V4 ip_v4_address;
			Ip_V6 ip_v6_address;
		} network_address;
		// The host's port in network byte order (big endian)
		u_short network_port = 0;
		// The host's ip address represented as a std::string
		// in host byte order (little endian).
		std::string ip_address_string;
	};
}

#endif // !HOSTINFORMATION_H

