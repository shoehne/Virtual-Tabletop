/*<------PCH------>*/
#include "VttClientPch.h"

#include "Core/ClientApp.h"

int main(int argc, char** argv) {

	Virtual_TT_Client::ClientApp* client_app = new Virtual_TT_Client::ClientApp();

	client_app->Run();
}