#pragma once
#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include <Virtual_Tabletop_API.h>

namespace Virtual_TT_Client {

	class ClientApp : public Virtual_TT_API::Application {

	public:
		ClientApp();
		~ClientApp();

		void Init();
		void Run();
	};
}

#endif // !CLIENT_APP_H

