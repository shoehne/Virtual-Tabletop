#pragma once

/*<------Core------>*/
#include "Core/Core.h"

/*<------Events------>*/
#include <Events/Event.h>
#include <Events/Application_Event.h>

namespace Virtual_TT_API {

	class VTT_API Application {

	public:
		Application() {}
		virtual ~Application() {};

		virtual void Init() {};
		virtual void Run() {};
	};
}