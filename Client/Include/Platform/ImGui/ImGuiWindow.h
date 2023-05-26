#pragma once
#ifndef IMGUIWINDOW_H
#define IMGUIWINDOW_H

#include "Core/Window.h"
#include "Events/Event.h"

namespace Vtt_Client {

	class ImGuiWindow {

	public:
		using EventCallbackFn = std::function<void(Vtt_Api::Event&)>;

		virtual ~ImGuiWindow() = default;

		virtual void Init() = 0;
		virtual void OnEvent(Vtt_Api::Event& event) = 0;
		virtual void OnUpdate() = 0;
		virtual void Render() = 0;

		bool IsActive() { return active; }
		void SetActive(bool activate) { active = activate; }
		void SetEventCallback(const EventCallbackFn& callback) { event_callback = callback; }

	protected:
		EventCallbackFn event_callback;
		bool active;
	};
}

#endif // !IMGUIWINDOW_H
