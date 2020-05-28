#pragma once

#include <Virtual_Tabletop_API.h>

class ServerApp : public Virtual_TT_API::Application {

public:
	ServerApp();
	~ServerApp();

	void Init() override;
	void Run() override;
};