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

uint16_t Vtt_Client::ImGuiWindowStack::PopWindow(Vtt_Client::ImGuiWindow* window) {

	Vtt_Client::ClientErrorCode error_code = NoError;
	auto it = std::find(windows.begin(),
		windows.begin() + insert_index,
		window);
	if (it != windows.begin() + insert_index) {

		windows.erase(it);
		insert_index--;


		return error_code;
	}
	else {

		return error_code = InvalidImGuiWnd;
	}

}

uint16_t Vtt_Client::ImGuiWindowStack::PopWindow(uint64_t window_id) {

	Vtt_Client::ClientErrorCode error_code = NoError;
	for (auto it = windows.begin(); it != windows.end(); it++) {
	
		if (uint64_t(it.operator*()->GetId() == window_id)) {
	
			windows.erase(it);
			insert_index--;
			return error_code;
		}
		else {

			return error_code = InvalidImGuiWndId;
		}
	}

}

uint16_t Vtt_Client::ImGuiWindowStack::PushWindow(Vtt_Client::ImGuiWindow* window) {

	windows.emplace(windows.begin() + insert_index,
		window);
	insert_index++;

	return Vtt_Client::ClientErrorCode(NoError);
}