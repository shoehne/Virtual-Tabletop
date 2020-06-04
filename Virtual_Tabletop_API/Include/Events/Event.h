#pragma once
#ifndef EVENT_H
#define EVENT_H

/*<------PCH------>*/
#include "VTT_API_PCH.h"

#include "Core/Core.h"
#include "Events/Event_Types.h"

namespace Virtual_TT_API {

	enum Event_Category {

		None = 0,
	};

	#define EVENT_CLASS_TYPE(type) static Event_Type Get_Static_Type() {return Event_Type::##type;}\
									virtual Event_Type Get_Event_Type() const override {return Get_Static_Type;}\
									virtual const char* Get_Name() const override {return #type;}

	#define EVENT_CLASS_CATEGORY(category) virtual int Get_Category_Flags() const override {return category;}

	class  Event {

		friend class Event_Dispatcher;
	
	public:
		virtual Event_Type Get_Event_Type() const = 0;
		virtual const char* Get_Name() const = 0;
		virtual int Get_Category_Flags() const = 0;
		virtual std::string To_String() const { return Get_Name(); }

		inline bool Is_In_Category(Event_Category category) {

			return Get_Category_Flags() & category;
		}
		
	protected:
		bool Handled = false;
	};

	class  Event_Dispatcher {

		template<typename T>
		using Event_Fn = std::function<bool(T&)>;
	public:
		Event_Dispatcher(Event& event) : event(event) {}

		template<typename T>
		bool Dispatch(Event_Fn<T> fn) {

			if (event.Get_Event_Type() == T::Get_Static_Type()) {

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
