#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include "Core/Core.h"
#include "Events/Event.h"

#include "imgui.h"

namespace Vtt_Client {

	class Window;

	// Main properties of the window (title, width, height)
	struct WindowProps {

		WindowProps(const std::wstring& name = L"",
			uint16_t x = 0,
			uint16_t y = 0,
			uint16_t w = 1280,
			uint16_t h = 720,
			Vtt_Client::Window* p = nullptr)
			: title(name), x_pos(x), y_pos(y), width(w), height(h), parent(p) {}

		std::wstring title;
		uint16_t x_pos, y_pos, width, height;
		Vtt_Client::Window* parent;
	};

	struct WindowData {

		WindowData(const std::wstring& name = L"",
			uint16_t x = 0,
			uint16_t y = 0,
			uint16_t w = 0,
			uint16_t h = 0,
			Vtt_Client::Window* p = nullptr)
			: title(name), x_pos(x), y_pos(y), width(w), height(h), parent(p) {}

		using EventCallbackFn = std::function<void(Vtt_Api::Event&)>;

		std::wstring title;
		uint16_t x_pos, y_pos, width, height;
		Vtt_Client::Window* parent;

		EventCallbackFn event_callback;
	};

	class Window {

	public:
		using EventCallbackFn = std::function<void(Vtt_Api::Event&)>;

		virtual ~Window() = default;

		virtual void BeginImGui() = 0;
		virtual void EndImGui() = 0;
		virtual uint16_t GetHeight() const = 0;
		virtual uint16_t GetWidth() const = 0;
		virtual uint16_t GetX() const = 0;
		virtual uint16_t GetY() const = 0;
		virtual void* GetNativeWindow() const = 0;
		virtual void* GetParentWindow() const = 0;
		virtual void Init(const WindowProps& props) = 0;
		virtual void OnUpdate() {}
		virtual void Render() = 0;
		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;

		static Vtt_Api::Ref<Window> Create(const WindowProps& props = WindowProps());
	};
}

#endif // !WINDOW_H
