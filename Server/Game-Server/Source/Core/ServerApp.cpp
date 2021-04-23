/*<------PCH------>*/
#include <VttServerPch.h>

#include <Core/ServerApp.h>

ServerApp::ServerApp() {

	Init();
}

ServerApp::~ServerApp() {


}

void ServerApp::Init() {

	Virtual_TT_API::Log::Init();
	VTT_SERVER_INFO("Initialised Log");
}

void ServerApp::Run() {

	while (true);
}