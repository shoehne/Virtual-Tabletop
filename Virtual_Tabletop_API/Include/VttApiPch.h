#pragma once
#ifndef VTT_PCH_H
#define VTT_PCH_H

//------STL---------------------------------------------------------------
//------------------------------------------------------------------------
#include <chrono>
#include <functional>
#include <limits>
#include <memory>
#include <thread>
#include <vector>

#include <string>
#include <sstream>
#include <iostream>
#include <ostream>
//------------------------------------------------------------------------
//------------------------------------------------------------------------

//------Windows Specific Includes-----------------------------------------
//------------------------------------------------------------------------
#ifdef VTT_PLATFORM_WINDOWS
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <Windows.h>
#endif // VTT_PLATFORM_WINDOWS
//------------------------------------------------------------------------
//------------------------------------------------------------------------


#endif
