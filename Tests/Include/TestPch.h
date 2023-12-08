#pragma once
#ifndef TESTPCH_H
#define TESTPCH_H
/*---
* gTest & gMock
---*/
#include "gtest/gtest.h"
#include "gmock/gmock.h"
/*---
* gTest & gMock End
---*/

/*---
* Virtual Tabletop API Core
---*/
#include "Core/Core.h"
#include "Core/UUID.h"
#ifdef PLATFORM_WINDOWS
#include "Core/KeycodesWin32.h"
#endif // PLATFORM_WINDOWS
/*---
* Virtual Tabletop API Core End
---*/

/*---
* Virtual Tabletop API Events
---*/
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"
/*---
* Virtual Tabletop API Events End
---*/

/*---
* Virtual Tabletop Client Core
---*/
#include "Core/ClientErrorCode.h"
//#include "Core/Window.h"
/*---
* Virtual Tabletop Client Core End
---*/

/*---
* Virtual Tabletop Client Platform Windows
---*/
//#include "Platform/Windows/WindowWindows.h"
/*---
* Virtual Tabletop Client Platform Windows End
---*/

/*---
* Virtual Tabletop Client Platform ImGui
---*/
#include "Platform/ImGui/ImGuiWindow.h"
#include "Platform/ImGui/ImGuiWindowStack.h"

/*---
* STL
---*/
#include <stdint.h>
#include <string>
/*---
* STL End
---*/
#endif // !TESTPCH_H