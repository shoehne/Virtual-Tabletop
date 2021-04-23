#pragma once
#ifndef NETWORKEVENT_H
#define NETWORKEVENT_H

#include "Events/Event.h"

namespace Virtual_Tt_Api {

	class NetworkEvent : public Virtual_Tt_Api::Event {

	public:
		EVENT_CLASS_CATEGORY(EventCategoryNetwork);
	};

	class NewConnectionEvent : public NetworkEvent {

	public:
		EVENT_CLASS_TYPE(New_Connection);
	};

	class MessageReceivedEvent : public NetworkEvent {

	public:
		EVENT_CLASS_TYPE(Message_Received);
	};

	class SocketStateEvent : public NetworkEvent {

	public:
		EVENT_CLASS_TYPE(Socket_State_Changed);
	};
}

#endif // !NETWORKEVENT_H

