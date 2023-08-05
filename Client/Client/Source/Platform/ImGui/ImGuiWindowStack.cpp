#include "VttClientPch.h"

#include "Platform/ImGui/ImGuiWindowStack.h"

Vtt_Client::ImGuiWindowStack::~ImGuiWindowStack() {

	for (ImGuiWindow* window : windows) {

		delete window;
	}
}

bool Vtt_Client::ImGuiWindowStack::IsEmpty() {

	return windows.empty();
}

void Vtt_Client::ImGuiWindowStack::PopWindow(Vtt_Client::ImGuiWindow* window) {

	auto it = std::find(windows.begin(),
		windows.begin() + insert_index,
		window);
	if (it != windows.begin() + insert_index) {

		windows.erase(it);
		insert_index--;
	}
}

void Vtt_Client::ImGuiWindowStack::PopWindow(uint64_t window_id) {

	for (auto it = windows.begin(); it != windows.end(); it++) {
	
		if (uint64_t(it.operator*()->GetId() == window_id)) {
	
			windows.erase(it);
			insert_index--;
			return;
		}
	}
}

void Vtt_Client::ImGuiWindowStack::PushWindow(Vtt_Client::ImGuiWindow* window) {

	windows.emplace(windows.begin() + insert_index,
		window);
	insert_index++;
}