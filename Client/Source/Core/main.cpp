/*<------PCH------>*/
#include <VTT_Client_PCH.h>

#include <Core/Client_App.h>

int main(int argc, char** argv) {

	Virtual_TT_Client::ClientApp* client_app = new Virtual_TT_Client::ClientApp();

	client_app->Run();
}