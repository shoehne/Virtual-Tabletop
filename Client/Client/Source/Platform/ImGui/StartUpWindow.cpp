#include "VttClientPch.h"

#include "Platform/ImGui/StartUpWindow.h"

Vtt_Client::StartUpWindow::StartUpWindow() {

	Init();
}

void Vtt_Client::StartUpWindow::Init() {

	flags |= ImGuiWindowFlags_NoCollapse;
}

void Vtt_Client::StartUpWindow::OnEvent(Vtt_Api::Event& event) {


}

void Vtt_Client::StartUpWindow::OnUpdate() {


}

void Vtt_Client::StartUpWindow::Render() {

	const ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImVec2 viewport_centre = viewport->GetWorkCenter();
	ImGui::SetNextWindowPos(ImVec2(viewport_centre.x - 500, viewport_centre.y - 270));
	ImGui::SetNextWindowSize(ImVec2(1000, 540));
	ImGui::OpenPopup("Virtual Tabletop");
	if (ImGui::BeginPopupModal("Virtual Tabletop")) {

		if (ImGui::Button("Close")) {

			uint64_t id = uint64_t(window_id);
			Vtt_Client::ImGuiWindowCloseEvent event(id);
			event_callback(event);
		}
		ImGui::EndPopup();
	}
}