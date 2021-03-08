#pragma once
#ifndef MESSAGETYPE_H
#define MESSAGETYPE_H

#include "VttApiPch.h"

#include <yojimbo.h>

namespace Virtual_Tt_Api {

	// MessageType to be used with the MessageFactory macros provided by yojimbo.
	// MessageType::COUNT is always at the end of the enum class. It's used to 
	// tell the yojimbo macro how many different message types exist.
	enum class MessageType : uint8_t {
		CHAT,
		COUNT
	};

	// Class declarations of all the messages listed in MessageType.
	class ChatMessage : public yojimbo::Message {

	public:
		ChatMessage() : message("") {}

		template <typename Stream>
		bool Serialize(Stream& stream) {

			serialize_string(stream,
				message,
				strlen(message));
			return true;
		}

		std::string message;

		YOJIMBO_VIRTUAL_SERIALIZE_FUNCTIONS();
	};
}

#endif // !MESSAGETYPE_H


