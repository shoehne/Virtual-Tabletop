#pragma once
#ifndef IMGUIWINDOWSTACK_H
#define IMGUIWINDOWSTACK_H

#include "Platform/ImGui/ImGuiWindow.h"

#include <vector>

namespace Vtt_Client {

	class ImGuiWindowStack {

	public:
		ImGuiWindowStack() = default;
		~ImGuiWindowStack();

		bool IsEmpty();
		uint16_t PopWindow(ImGuiWindow* window);
		uint16_t PopWindow(uint64_t window_id);
		uint16_t PushWindow(ImGuiWindow* window);

		std::vector<ImGuiWindow*>::iterator begin() { return windows.begin(); }
		std::vector<ImGuiWindow*>::iterator end() { return windows.end(); }
		std::vector<ImGuiWindow*>::reverse_iterator rbegin() { return windows.rbegin(); }
		std::vector<ImGuiWindow*>::reverse_iterator rend() { return windows.rend(); }

		std::vector<ImGuiWindow*>::const_iterator begin() const { return windows.begin(); }
		std::vector<ImGuiWindow*>::const_iterator end() const { return windows.end(); }
		std::vector<ImGuiWindow*>::const_reverse_iterator rbegin() const{ return windows.rbegin(); }
		std::vector<ImGuiWindow*>::const_reverse_iterator rend() const { return windows.rend(); }

	private:
		std::vector<ImGuiWindow*> windows;
		unsigned int insert_index = 0;
	};
}

#endif // !IMGUIWINDOWSTACK_H

