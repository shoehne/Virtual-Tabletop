/*<------PCH------>*/
#include <VttServerPch.h>

#include <Core/ServerApp.h>

ServerApp::ServerApp() {

	Init();
}

ServerApp::~ServerApp() {


}

void ServerApp::Init() {

	Vtt_Api::Log::Init();
	VTT_SERVER_INFO("Initialised Log");
}

void ServerApp::Run() {

	while (true);
}