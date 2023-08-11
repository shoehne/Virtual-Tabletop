/*<------PCH------>*/
#include "VttClientPch.h"

#include "Core/ClientApp.h"
#ifdef PLATFORM_WINDOWS
#pragma comment(linker, "/ENTRY:mainCRTStartup")
#endif // PLATFORM_WINDOWS


int main(int argc, char** argv) {

	#ifdef DEBUG | RELEASE && PLATFORM_WINDOWS
	AllocConsole();
	freopen("CONOUT$",
		"w+",
		stdout);
	freopen("CONOUT$",
		"w+",
		stderr);
	#endif // DEBUG && PLATFORM_WINDOWS

	Vtt_Client::ClientApp* client_app = new Vtt_Client::ClientApp();

	if (client_app->Init()) {

		client_app->Run();
	}
}