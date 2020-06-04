#pragma once
#ifndef SERVER_APP_H
#define SERVER_APP_H

#include <Virtual_Tabletop_API.h>

class ServerApp : public Virtual_TT_API::Application {

public:
	ServerApp();
	~ServerApp();

	void Init();
	void Run();
};

#endif