#pragma once
#ifndef SERVER_APP_H
#define SERVER_APP_H

#include <VirtualTabletopApi.h>

class ServerApp : public Virtual_TT_API::Application {

public:
	ServerApp();
	~ServerApp();

	void Init();
	void Run();
};

#endif