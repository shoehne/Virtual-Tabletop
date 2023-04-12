#pragma once
#ifndef WINDOWWINDOWS_H
#define WINDOWWINDOWS_H

#include "Core/KeycodesWin32.h"
#include "Core/Window.h"

namespace Vtt_Client {

	class WindowWindows : public Window {
	
	public:
		WindowWindows(const WindowProps& props);
		virtual ~WindowWindows();

		virtual void BeginImGui() override;
		virtual void EndImGui() override;
		virtual uint16_t GetHeight() const override;
		virtual void* GetNativeWindow() const override { return window_handle; };
		virtual void* GetParentWindow() const override { return window_data->parent; };
		virtual uint16_t GetWidth() const override;
		virtual uint16_t GetX() const override;
		virtual uint16_t GetY() const override;
		virtual void OnUpdate() override;
		virtual void Render() override;
		virtual void SetEventCallback(const EventCallbackFn& callback) override;

	private:

		virtual void Init(const WindowProps& props) override;
		virtual void Shutdown();

		ImGuiContext* imgui_context;
		ImGuiIO io;
		WindowData* window_data;
		HWND window_handle;
	};
}
#endif // !WINDOWWINDOWS_H

