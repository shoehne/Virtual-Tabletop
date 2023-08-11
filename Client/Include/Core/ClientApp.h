#pragma once
#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include <VirtualTabletopApi.h>

#include "Core/Window.h"
#include "Events/ApplicationEvent.h"
#include "Platform/ImGui/ImGuiWindowStack.h"

namespace Vtt_Client {

	class ClientApp : public Vtt_Api::Application {

	public:
		ClientApp();
		~ClientApp();
		
		virtual bool Init() override;
		const Vtt_Api::Ref<Window> GetMainWindow();
		virtual void OnEvent(Vtt_Api::Event& event) override;
		virtual void Run() override;

	private:
		bool OnImGuiWndClose(Vtt_Client::ImGuiWindowCloseEvent& event);
		bool OnWindowClose(Vtt_Api::WindowCloseEvent& event);
		void PopImGuiWindow(ImGuiWindow* window);
		void PopImGuiWindow(uint64_t window_id);
		void PushImGuiWindow(ImGuiWindow* window);
		
		ImGuiWindowStack imgui_windows;
		Vtt_Api::Ref<Window> main_window;
	};
}

#endif // !CLIENT_APP_H