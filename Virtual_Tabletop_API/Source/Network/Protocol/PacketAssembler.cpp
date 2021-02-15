//------PCH------
#include "VttApiPch.h"

#include "Network/Protocol/PacketAssembler.h"

namespace Virtual_Tt_Api {

	PacketAssembler::PacketAssembler() {}
	PacketAssembler::~PacketAssembler() {}

	char PacketAssembler::Build_Packet(int message_type,
		void* data,
		uint32_t data_size) {

		return 0;
	}

	char PacketAssembler::Serialise_Chat_Message(char message) {

		return 0;
	}

	char PacketAssembler::Serialise_Connection(uint8_t message) {

		return 0;
	}

	char PacketAssembler::Serialise_Position(std::vector<int32_t> position) {

		return 0;
	}
}