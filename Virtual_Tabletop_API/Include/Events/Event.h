#pragma once
#ifndef EVENT_H
#define EVENT_H

//------PCH----------------------------------------------------------------
//-------------------------------------------------------------------------
#include "VttApiPch.h"
//-------------------------------------------------------------------------
//-------------------------------------------------------------------------

#include "Core/Core.h"
//#include "Events/EventTypes.h"

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

	enum EventCategory {

		None = 0,
		EventCategoryInput			= BIT(0),
		EventCategoryKeyboard		= BIT(1),
		EventCategoryMouse			= BIT(2),
		EventCategoryMouseButton	= BIT(3),
		EventCategoryNetwork		= BIT(4)
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const { return GetStaticType(); }\
								virtual const char* GetName() const { return #type; }

	#define EVENT_CLASS_CATEGORY(category) virtual int get_category_flags() const override { return category; }

	class  Event {

		friend class EventDispatcher;
	
	public:
		virtual EventType get_event_type() const = 0;
		virtual const char* get_name() const = 0;
		virtual int get_category_flags() const = 0;
		virtual std::string To_String() const { return get_name(); }

		inline bool Is_In_Category(EventCategory category) {

			return get_category_flags() & category;
		}
		
	protected:
		bool handled = false;
	};

	class  EventDispatcher {

		template<typename T>
		using Event_Fn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& event) : event(event) {}

		template<typename T>
		bool Dispatch(Event_Fn<T> fn) {

			if (event.get_event_type() == T::get_static_type()) {

				event.Handled = fn(*(T*)&event);
			}
		}

	private:
		Event& event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {

		return os << e.To_String();
	}
}

#endif
