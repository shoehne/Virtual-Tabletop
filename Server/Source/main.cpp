/*<------PCH------>*/
#include <VttServerPch.h>

#include <Core/ServerApp.h>

int main(int argc, char** argv) {

	ServerApp* server_app = new ServerApp();

	server_app->Run();
}