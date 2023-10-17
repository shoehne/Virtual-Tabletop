#pragma once
/*---
* Google Test
---*/
#include "gtest/gtest.h"
/*---
* Google Test End
---*/

/*---
* Virtual Tabletop API Core
---*/
#include "Core/Core.h"
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
#include "Core/ClientApp.h"
#include "Core/Window.h"
/*---
* Virtual Tabletop Client Core End
---*/

/*---
* Virtual Tabletop Client Platform Windows
---*/
#include "Platform/Windows/WindowWindows.h"
/*---
* Virtual Tabletop Client Platform Windows End
---*/
/*---
* STL
---*/
#include <string>
/*---
* STL End
---*/