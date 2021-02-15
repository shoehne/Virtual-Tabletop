#pragma once
#ifndef PACKETASSEMBLER_H
#define PACKETASSEMBLER_H

#include "Network/Protocol/packet.pb.h"

namespace Virtual_Tt_Api {
	
	// Defines what type of message should be packed
	// and whether the data is time critical or needs to be 
	// sent reliably.
	enum class MessageType : uint32_t {

		NONE = 0,
		// Reliable
		CHAT_MESSAGE,
		// Reliable
		CONNECTION,
		// Time critical
		POSITION
	};

	enum class ConnectionHandler : uint8_t {

		NONE = 0,
		CONNECTION_REQUESTED,
		CONNECTION_ACCEPTED,
		CONNECTION_DENIED,
		CONNECTION_DENIED_BLOCKED,
		DISCONNECTED,
		DISCONNECTED_TIMEOUT
	};

	struct PacketAssembler {

	public:
		// Default constructor.
		PacketAssembler();
		// Destructor
		~PacketAssembler();

		// Function to build a packet. Will build the packet
		// according to the specified message_type. Packet header is
		// automatically added.
		// Depending on the size of the data the data will be automatically
		// split into slices or fragments.
		// TO DO: Some form of encryption layer to be built into the packet.
		char Build_Packet(int message_type,
			void* data,
			uint32_t data_size);
		char Serialise_Chat_Message(char message);
		char Serialise_Connection(uint8_t message);
		char Serialise_Position(std::vector<int32_t> position);
	};
}

#endif // !PACKETASSEMBLER_H

