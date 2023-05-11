#pragma once
#ifndef VISUALCODEEDITOR_H
#define VISUALCODEEDITOR_H

#include "Platform/ImGui/ImGuiWindow.h"

namespace Vtt_Client {

	class VisualCodeEditor : public ImGuiWindow {

	public:
		VisualCodeEditor();
		~VisualCodeEditor() = default;

		virtual void Init() override;
		virtual void OnEvent(Vtt_Api::Event& event) override;
		virtual void OnUpdate() override;
		virtual void Render() override;

		
	};
}

#endif // !VISUALCODEEDITOR_H

