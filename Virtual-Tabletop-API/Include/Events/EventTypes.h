#pragma once
#ifndef EVENT_TYPES_H
#define EVENT_TYPES_H

namespace Virtual_Tt_Api {

	enum class EventType {

		//------No event type----------------------------------------------
		//-----------------------------------------------------------------
		None,
		//------Input Event------------------------------------------------
		//-----------------------------------------------------------------
		Key_Pressed,
		Key_Released,
		Mouse_Scrolled,
		//------Network Event----------------------------------------------
		//-----------------------------------------------------------------
		Message_Received,
		New_Connection,
		Socket_State_Changed,
		//------Window Event-----------------------------------------------
		//-----------------------------------------------------------------
		Window_Close,
		Window_Resize
	};
}

#endif // !EVENT_TYPES_H

