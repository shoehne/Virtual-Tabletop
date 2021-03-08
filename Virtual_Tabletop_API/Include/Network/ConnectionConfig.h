#pragma once
#ifndef CLIENTCONFIG_H
#define CLIENTCONFIG_H

#include "VttApiPch.h"

#include <yojimbo.h>

namespace Virtual_Tt_Api {

	enum class Channel : uint8_t {

		RELIABLE,
		UNRELIABLE,
		COUNT
	};

	struct ConnectionConfig : yojimbo::ClientServerConfig {

		ConnectionConfig() {

			numChannels = 2;
			channel[static_cast<uint8_t>(Channel::RELIABLE)].type = yojimbo::CHANNEL_TYPE_RELIABLE_ORDERED;
			channel[static_cast<uint8_t>(Channel::UNRELIABLE)].type = yojimbo::CHANNEL_TYPE_UNRELIABLE_UNORDERED;
		}
	};
}

#endif // !CLIENTCONFIG_H

