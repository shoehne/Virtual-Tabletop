/*<------PCH------>*/
#include <VttClientPch.h>

#include <Core/ClientApp.h>

namespace Virtual_TT_Client {

	ClientApp::ClientApp() {


	}

	ClientApp::~ClientApp() {


	}

	void ClientApp::Init() {

		Virtual_TT_API::Log::Init();
		VTT_SERVER_INFO("Initialised Log");
	}

	void ClientApp::Run() {

		while (true);
	}
}