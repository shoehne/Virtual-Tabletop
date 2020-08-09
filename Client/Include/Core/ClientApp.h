#pragma once
#ifndef CLIENT_APP_H
#define CLIENT_APP_H

#include <VirtualTabletopApi.h>

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

