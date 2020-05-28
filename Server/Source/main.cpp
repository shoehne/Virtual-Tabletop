/*<------PCH------>*/
#include <VTT_Server_PCH.h>

#include <Core/Server_App.h>

int main(int argc, char** argv) {

	ServerApp* server_app = new ServerApp();

	server_app->Run();
}