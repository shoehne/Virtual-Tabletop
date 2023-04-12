#pragma once
#ifndef APPLICATION_EVENT_H
#define APPLICATION_EVENT_H

#include "Events/Event.h"

namespace Vtt_Api {

	class ApplicationUpdateEvent : public Event {

	public:
		ApplicationUpdateEvent() = default;

		EVENT_CLASS_TYPE(APPLICATION_UPDATE);
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION);
	};

	class WindowCloseEvent : public Event {

	public:
		WindowCloseEvent() = default;

		EVENT_CLASS_TYPE(WINDOW_CLOSE);
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION);
	};

	class WindowResizeEvent : public Event {

	public:
		WindowResizeEvent(unsigned int w,
			unsigned int h)
			: width(w), height(h) {}

		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }

		std::string ToString() const override {

			std::stringstream stream;
			stream << "WindowResizeEvent: " << width << "," << height;
			return stream.str();
		}

		EVENT_CLASS_TYPE(WINDOW_RESIZED);
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION);

	private:
		unsigned int width, height;
	};

	class WindowMoveEvent : public Event {

	public:
		WindowMoveEvent(unsigned int x,
			unsigned int y)
			: x_pos(x), y_pos(y){}

		unsigned int GetX() const { return x_pos; }
		unsigned int GetY() const { return y_pos; }

		std::string ToString() const override {

			std::stringstream stream;
			stream << "WindowMoveEvent: X: " << x_pos << ", Y: " << y_pos;
			return stream.str();
		}

		EVENT_CLASS_TYPE(WINDOW_MOVED);
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_APPLICATION);

	private:
		unsigned int x_pos, y_pos;
	};
}

#endif // !APPLICATION_EVENT_H

