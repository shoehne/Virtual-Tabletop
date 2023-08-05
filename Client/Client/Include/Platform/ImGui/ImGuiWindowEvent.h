#pragma once
#ifndef IMGUIWINDOWEVENT_H
#define IMGUIWINDOWEVENT_H

#include "Events/Event.h"

namespace Vtt_Client {

	class ImGuiWindowCloseEvent : public Vtt_Api::Event {

	public:
		ImGuiWindowCloseEvent(uint64_t id)
			: window_id(id) {}

		uint64_t GetId() { return window_id; }

		Vtt_Api::EventCategory category = Vtt_Api::EventCategory::EVENT_CATEGORY_IMGUI;

		EVENT_CLASS_TYPE(IMGUI_WND_CLOSE);
		EVENT_CLASS_CATEGORY(category);

	private:
		uint64_t window_id;
	};
}

#endif // !IMGUIWINDOWEVENT_H

