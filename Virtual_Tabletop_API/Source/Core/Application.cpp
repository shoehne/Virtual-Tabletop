/*<------PCH------>*/
#include <VttApiPch.h>

#include <Core/Application.h>

namespace Virtual_TT_API {

	Application::Application() {


	}

	Application::~Application() {


	}

	void Application::Stop() {

		is_running = false;
	}
}