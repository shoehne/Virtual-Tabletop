#pragma once
#ifndef STARTUPWINDOW_H
#define STARTUPWINDOW_H

#include "Platform/ImGui/ImGuiWindow.h"

namespace Vtt_Client {

	class StartUpWindow : public ImGuiWindow {

	public:
		StartUpWindow();
		virtual ~StartUpWindow() = default;

		virtual void Init() override;
		virtual void OnEvent(Vtt_Api::Event& event) override;
		virtual void OnUpdate() override;
		virtual void Render() override;

	private:
		bool is_open = true;
		ImGuiWindowFlags flags = 0;
	};
}

#endif // !STARTUPWINDOW_H
