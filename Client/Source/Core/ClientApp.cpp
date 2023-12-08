#include "VttClientPch.h"

#include "Core/ClientApp.h"

Vtt_Client::ClientApp::ClientApp() {


}

Vtt_Client::ClientApp::~ClientApp() {


}

bool Vtt_Client::ClientApp::Init() {

	Vtt_Api::Log::Init();
	VTT_API_INFO("Initialised Log");

	// Create the main window with the default size and position.
	// Use "Virtual Tabletop" as the title for the window.
	// TO DO: Support for different languages -> translated titles.
	try {

		std::wstring name = L"Virtual Tabletop";
		main_window = Window::Create(WindowProps(name));
		main_window->SetEventCallback(BIND_EVENT(ClientApp::OnEvent));
		StartUpWindow* startup = new StartUpWindow();
		startup->SetEventCallback(BIND_EVENT(ClientApp::OnEvent));
		imgui_windows.PushWindow(startup);
	}
	catch (std::exception& e) {

		VTT_CLIENT_ERROR("Failed to create main window!\nError: {0}",
			e.what());

		return false;
	}

	VTT_CLIENT_INFO("Client initialised without problems.");

	return true;
}

const Vtt_Api::Ref<Vtt_Client::Window> Vtt_Client::ClientApp::GetMainWindow() {

	return main_window;
}

void Vtt_Client::ClientApp::OnEvent(Vtt_Api::Event& event) {

	Vtt_Api::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Vtt_Api::WindowCloseEvent>(BIND_EVENT(OnWindowClose));
	dispatcher.Dispatch<Vtt_Client::ImGuiWindowCloseEvent>(BIND_EVENT(OnImGuiWndClose));
}

void Vtt_Client::ClientApp::Run() {

	while (Vtt_Api::Application::IsRunning()) {

		main_window->OnUpdate();
		main_window->BeginImGui();
		for (ImGuiWindow* window : imgui_windows) {
		
			window->Render();
			if (imgui_windows.IsEmpty()) {

				break;
			}
		}
		main_window->Render();
		main_window->EndImGui();
	}
}

bool Vtt_Client::ClientApp::OnImGuiWndClose(Vtt_Client::ImGuiWindowCloseEvent& event) {

	uint16_t error_code = PopImGuiWindow(event.GetId());
	if (error_code == 0) {

		return true;
	}
	else {

		VTT_CLIENT_ERROR("Failed to close window!/nWindow ID: {0}/nErrorcode: {1}",
			event.GetId(),
			error_code);

		return false;
	}
}

bool Vtt_Client::ClientApp::OnWindowClose(Vtt_Api::WindowCloseEvent& event) {

	Vtt_Api::Application::Stop();
	return true;
}

uint16_t Vtt_Client::ClientApp::PopImGuiWindow(ImGuiWindow* window) {

	return imgui_windows.PopWindow(window);
}

uint16_t Vtt_Client::ClientApp::PopImGuiWindow(uint64_t window_id) {

	return imgui_windows.PopWindow(window_id);
}

uint16_t Vtt_Client::ClientApp::PushImGuiWindow(ImGuiWindow* window) {

	return imgui_windows.PushWindow(window);
}
