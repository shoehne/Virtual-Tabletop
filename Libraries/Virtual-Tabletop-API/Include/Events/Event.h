#pragma once
#ifndef EVENT_H
#define EVENT_H

#include "Core/Core.h"

#include <functional>
#include <ostream>
#include <sstream>

namespace Vtt_Api {

	enum class EventType {

		None = 0,
		APPLICATION_TICK,
		APPLICATION_UPDATE,
		IMGUI_WND_CLOSE,
		KEY_PRESSED,
		KEY_RELEASED,
		MOUSE_BUTTON_MOVED,
		MOUSE_BUTTON_PRESSED,
		MOUSE_BUTTON_RELEASED,
		MOUSE_BUTTON_SCROLLED,
		SQL_DELETE_QUERY,
		SQL_INSERT_QUERY,
		SQL_QUERY_FINISHED,
		SQL_SELECT_QUERY,
		SQL_UPDATE_QUERY,
		WINDOW_CLOSE,
		WINDOW_FOCUS,
		WINDOW_LOST_FOCUS,
		WINDOW_MOVED,
		WINDOW_RESIZED
	};

	enum EventCategory {

		None = 0,
		EVENT_CATEGORY_APPLICATION = BIT(1),
		EVENT_CATEGORY_INPUT = BIT(2),
		EVENT_CATEGORY_KEYBOARD = BIT(3),
		EVENT_CATEGORY_MOUSE = BIT(4),
		EVENT_CATEGORY_MOUSE_BUTTON = BIT(5),
		EVENT_CATEGORY_IMGUI = BIT(6)
	};

	class Event {

		friend class EventDispatcher;
	public:
		virtual int GetCategoryFlags() const = 0;
		virtual EventType GetEventType() const = 0;

		bool IsHandled() { return handled; }
		inline bool IsInCategory(EventCategory category) {

			return GetCategoryFlags() & category;
		}

		// Debug functions
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); }
		
	protected:
		bool handled = false;
	};

	class EventDispatcher {

		template<typename T>
		using EventFn = std::function<bool(T&)>;
	public:
		EventDispatcher(Event& e) : event(e) {}

		template<typename T>
		bool Dispatch(EventFn<T> func) {

			if (event.GetEventType() == T::GetStaticType()) {

				event.handled = func(*(T*)&event);
				return true;
			}
		}

	private:
		Event& event;
	};
	
	inline std::ostream& operator<<(std::ostream& os,
		const Event& e) {

		return os << e.ToString();
	}
}

// Macro to simplify implementation of the virtual event functions that need to be implemented
// for each child class of Vtt_Api::Event.
#ifndef DISTRIBUTION
#define EVENT_CLASS_TYPE(type) static Vtt_Api::EventType GetStaticType() {return Vtt_Api::EventType::##type;}\
								virtual Vtt_Api::EventType GetEventType() const override {return GetStaticType();}\
								virtual const char* GetName() const override {return #type;}
#else
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() {return EventType::##type;}\
								virtual EventType GetEventType() const override {return GetStaticType();}
#endif

#define  EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category;}

#endif // !EVENT_H
