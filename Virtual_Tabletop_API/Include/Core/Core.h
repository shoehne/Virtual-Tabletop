#pragma once
#ifndef CORE_H
#define CORE_H

#ifdef VTT_PLATFORM_WINDOWS
	#ifdef VTT_BUILD_DLL
		#define VTT_API __declspec(dllexport)
	#else
		#define VTT_API __declspec(dllimport)
	#endif
#elif VTT_PLATFORM_LINUX
	#ifdef VTT_BUILD_SO
		#define VTT_API __attribute__((visibility("default")))
	#endif
#else
	#error Virtual Tabletop only supports Windows and Linux.
#endif

#define BIT(x) = (1 << x)

#endif
