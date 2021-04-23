#pragma once
#ifndef VTTMESSAGEFACTORY_H
#define VTTMESSAGEFACTORY_H

#include "Network/Messages/MessageType.h"

namespace Virtual_Tt_Api {

	YOJIMBO_MESSAGE_FACTORY_START(VttMessageFactory, static_cast<uint8_t>(MessageType::COUNT));
	YOJIMBO_DECLARE_MESSAGE_TYPE(static_cast<uint8_t>(MessageType::CHAT), ChatMessage);
	YOJIMBO_MESSAGE_FACTORY_FINISH();
}



#endif // !MESSAGEFACTORY_H

