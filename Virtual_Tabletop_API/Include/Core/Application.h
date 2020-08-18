#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H
/*<------Core------>*/
#include "Core/Core.h"

/*<------Events------>*/
#include <Events/Event.h>
#include <Events/ApplicationEvent.h>

namespace Virtual_TT_API {

	class  Application {

	public:
		Application();
		virtual ~Application();

		virtual void Init() = 0;
		virtual void Run() = 0;
		virtual void Stop();

	private:
		bool is_running = true;
	};
}

#endif