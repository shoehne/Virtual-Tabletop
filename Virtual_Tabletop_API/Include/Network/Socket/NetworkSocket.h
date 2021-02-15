#pragma once
#ifndef NETWORKSOCKET_H
#define NETWORKSOCKET_H

//------PCH-----------------------------------------------------------------
//--------------------------------------------------------------------------
#include "VttApiPch.h"
//--------------------------------------------------------------------------
//--------------------------------------------------------------------------

#ifdef VTT_PLATFORM_WINDOWS
#pragma comment(lib, "ws2_32.lib")
#endif // VTT_PLATFORM_WINDOWS


#ifdef VTT_PLATFORM_LINUX
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netdb.h>
#include <fcntl.h>
#endif

#include "Core/Log.h"
#include "Network/HostInformation.h"

#define MAX_HOST_NAME 255

namespace Virtual_Tt_Api {

	enum class SocketState {

		None = 0,
		BOUND,
		CONNECTED,
		CLOSING,
		DISCONNECTED,
		LISTENING
	}; 

	class NetworkSocket {

	public:
		// Constructor & destructor
		NetworkSocket() {};
		~NetworkSocket() {};
		
		// Virtual functions
		virtual HostInformation Get_Socket_Host_Info() = 0;
		virtual SocketState Get_Socket_State() = 0;
		virtual bool Socket_Close() = 0;
		virtual bool Socket_Create(int addr_info_family,
			int addr_info_flag) = 0;
		virtual bool Socket_Create(int addr_info_family, 
			int addr_info_flag,
			std::string ip_address) = 0;
		virtual bool Socket_Initialise() = 0;
		virtual int Socket_Receive(HostInformation& sender_socket,
			void* data,
			int data_size) = 0;
		virtual bool Socket_Send(const HostInformation& destination,
			const void* data,
			int size) = 0;
		virtual void Socket_Shutdown() = 0;
	};
}

#endif // !NETWORKSOCKET_H

