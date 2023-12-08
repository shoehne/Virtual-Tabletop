#pragma once
#ifndef KEYEVENT_H
#define KEYEVENT_H

#include "Events/Event.h"
// Win32 keycodes
#ifdef PLATFORM_WINDOWS
#include "Core/KeycodesWin32.h"
#endif // PLATFORM_WINDOWS



namespace Vtt_Api {

	class KeyEvent : public Event {

	public:
		KeyCode GetKeyCode() const { return key_code; }

		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_KEYBOARD | EVENT_CATEGORY_INPUT);

	protected:
		KeyEvent(const KeyCode code) 
			: key_code(code) {}
		KeyEvent() = default;

		KeyCode key_code;
	};

	class KeyPressedEvent : public KeyEvent {

	public:
		KeyPressedEvent(const KeyCode code,
			bool repeat = false)
			: KeyEvent(key_code), is_repeat(repeat) {}

		bool IsRepeat() const { return is_repeat; }

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyPressedEvent: " << key_code << " (repeat = " << is_repeat << ")";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_PRESSED);
	private:
		bool is_repeat;
	};

	class KeyReleasedEvent : public KeyEvent {

	public:
		KeyReleasedEvent(const KeyCode code)
			: KeyEvent(code) {}

		std::string ToString() const override {

			std::stringstream ss;
			ss << "KeyReleasedEvent: " << key_code;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KEY_RELEASED);
	};
}

#endif // !KEYEVENT_H

