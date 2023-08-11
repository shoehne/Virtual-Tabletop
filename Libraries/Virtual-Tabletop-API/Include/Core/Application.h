#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "Core/Core.h"
#include <Events/Event.h>
#include <Events/ApplicationEvent.h>

namespace Vtt_Api {

	class Application {

	public:
		Application() = default;
		virtual ~Application() = default;

		virtual bool Init() = 0;
		bool IsRunning() { return is_running; }
		virtual void OnEvent(Event& event) = 0;
		virtual void Run() = 0;
		virtual void Stop() { is_running = false; }

	private:
		bool is_running = true;
	};
}

#endif