#include "VttClientPch.h"

#include "Core/Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowWindows.h"
#endif // WINDOWS

Vtt_Api::Ref<Vtt_Client::Window> Vtt_Client::Window::Create(const Vtt_Client::WindowProps& props) {

	#ifdef PLATFORM_WINDOWS
	return Vtt_Api::CreateRef<Vtt_Client::WindowWindows>(props);
	#else
	VTT_CLIENT_ERROR("Impossible to create window on this platform. Platform is not supported");
	#endif // WINDOWS
}