#pragma once
#ifndef VIRTUAL_CLIENT_PCH_H
#define VIRTUAL_CLIENT_PCH_H

#include "Core/Log.h"

#include "Events/ApplicationEvent.h"

// ImGuiWindow's and their events
#include "Platform/ImGui/ImGuiWindowEvent.h"
#include "Platform/ImGui/StartUpWindow.h"

#include <exception>
#include <stdlib.h>
#include <fstream>

#include "yaml-cpp/yaml.h"

#ifdef PLATFORM_WINDOWS
#include <Windows.h>
#include <windef.h>
#include <d3d11.h>
#include <d3dcompiler.h>
#include <d3d12.h>
#include <dxgi1_6.h>
#include <tchar.h>

// Windows specific ImGui implementations.
#include "backends/imgui_impl_win32.h"
#include "backends/imgui_impl_dx11.h"
#include "backends/imgui_impl_dx12.h"
#endif // PLATFORM_WINDOWS

#endif // !VIRTUAL_CLIENT_PCH_H
