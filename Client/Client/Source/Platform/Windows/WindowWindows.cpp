#include "VttClientPch.h"

#include "Platform/Windows/WindowWindows.h"
#include "Events/ApplicationEvent.h"
#include "Events/KeyEvent.h"

// Windows callback function
LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam);
// Forward declare message handler from imgui_impl_win32.cpp
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, 
	UINT msg, 
	WPARAM wParam, 
	LPARAM lParam);
// Forward declaration of helper functions.
void CleanUpDeviceD3D();
void CleanUpRenderTarget();
bool CreateDeviceD3D(HWND hwnd);
void CreateRenderTarget();

// D3D device related variables needed for helper functions declared above.
static ID3D11Device* d3d_device = NULL;
static ID3D11DeviceContext* d3d_device_context = NULL;
static IDXGISwapChain* swap_chain = NULL;
static ID3D11RenderTargetView* main_render_target_view = NULL;

Vtt_Client::WindowWindows::WindowWindows(const WindowProps& props) {

	Init(props);
}

Vtt_Client::WindowWindows::~WindowWindows() {

	Shutdown();
}

void Vtt_Client::WindowWindows::BeginImGui() {

	// Start the ImGui frame.
	ImGui::SetCurrentContext(imgui_context);
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (ImGui::BeginMainMenuBar()) {

		ImGui::EndMainMenuBar();
	}

	// Set up the dockspace for the main window.
	// Dockspace won't have a background so it will be rendered on top of a separate 3D-view.
	if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable) {

		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	}
	ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(),
		ImGuiDockNodeFlags_PassthruCentralNode);
}

void Vtt_Client::WindowWindows::EndImGui() {

	// Render
	const float clear_colour[4] = { 0.14f,
	0.14f,
	0.14f,
	0.00f };
	ImGui::Render();
	d3d_device_context->OMSetRenderTargets(1,
		&main_render_target_view,
		NULL);
	d3d_device_context->ClearRenderTargetView(main_render_target_view,
		clear_colour);
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	// Present with V-Sync
	swap_chain->Present(0,
		0);
}

uint16_t Vtt_Client::WindowWindows::GetHeight() const {

	return window_data->height;
}

uint16_t Vtt_Client::WindowWindows::GetWidth() const {

	return window_data->width;
}

uint16_t Vtt_Client::WindowWindows::GetX() const {

	return window_data->x_pos;
}

uint16_t Vtt_Client::WindowWindows::GetY() const {

	return window_data->y_pos;
}

void Vtt_Client::WindowWindows::OnUpdate() {

	MSG msg;
	ZeroMemory(&msg,
		sizeof(msg));
	// Peek for a message without blocking the thread
	if (PeekMessage(&msg,
		window_handle,
		0,
		0,
		PM_REMOVE)) {

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void Vtt_Client::WindowWindows::Render() {
	
	#ifdef DEBUG
	ImGui::ShowDemoWindow((bool*)true);
	#endif // DEBUG
}

void Vtt_Client::WindowWindows::SetEventCallback(const EventCallbackFn& callback) {

	window_data->event_callback = callback;
}

void Vtt_Client::WindowWindows::Init(const WindowProps& props) {

	// Load position and size settings from config.yaml.
	// If the config.yaml file can't be opened use default values.
	// Default values: x=0, y=0, w=1280, h=720
	bool use_default = false;
	YAML::Node config;
	try {

		config = YAML::LoadFile("config.yaml");
	}
	catch (std::exception& e) {

		VTT_CLIENT_ERROR("Failed to load config file. Error: {0}\nUsing default values.",
			e.what());
		use_default = true;
	}

	// Create a new WindowData object and a new WindowHandle for this window.
	window_data = new (std::nothrow) WindowData;
	if (window_data == NULL) {

		return;
	}

	// Register the window class.
	const wchar_t CLASS_NAME[] = L"Virtual Tabletop";
	window_data->title = props.title;
	if (use_default) {

		window_data->x_pos = props.x_pos;
		window_data->y_pos = props.y_pos;
		window_data->height = props.height;
		window_data->width = props.width;
	}
	else {

		YAML::Node display = config["Display"];
		window_data->x_pos = display["X"].as<int>();
		window_data->y_pos = display["Y"].as<int>();
		window_data->width = display["Width"].as<int>();
		window_data->height = display["Height"].as<int>();
	}
	window_data->parent = props.parent;

	WNDCLASS window_class = {};
	
	window_class.lpfnWndProc = WindowProc;
	window_class.hInstance = GetModuleHandle(0);
	window_class.lpszClassName = CLASS_NAME;

	RegisterClass(&window_class);

	// Create the window
	DWORD wnd_style = WS_OVERLAPPEDWINDOW;
	window_handle = CreateWindowEx(0,
		CLASS_NAME,
		NULL,
		wnd_style,
		// Initial position and size of the window
		window_data->x_pos,
		window_data->y_pos,
		window_data->width,
		window_data->height,
		(HWND)window_data->parent,
		NULL,
		GetModuleHandle(0),
		window_data);

	if (window_handle == NULL) {

		VTT_CLIENT_ERROR("Failed to create window!");
		return;
	}

	// Initialise Direct3D.
	if (!CreateDeviceD3D(window_handle)) {
	
		CleanUpDeviceD3D();
		UnregisterClass(window_class.lpszClassName,
			window_class.hInstance);
		return;
	}

	ShowWindow(window_handle,
		SW_SHOW);
	UpdateWindow(window_handle);

	// Setup Dear ImGui context.
	IMGUI_CHECKVERSION();
	imgui_context = ImGui::CreateContext();
	ImGui::SetCurrentContext(imgui_context);
	io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {

		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	// Setup platform/renderer bindings.
	ImGui_ImplWin32_Init(window_handle);
	ImGui_ImplDX11_Init(d3d_device,
		d3d_device_context);
}

void Vtt_Client::WindowWindows::Shutdown() {

	PostQuitMessage(0);
}

// Helper functions
void CleanUpDeviceD3D() {

	CleanUpRenderTarget();
	if (swap_chain) {

		swap_chain->Release();
		swap_chain = NULL;
	}
	if (d3d_device_context) {

		d3d_device_context->Release();
		d3d_device_context = NULL;
	}
	if (d3d_device) {

		d3d_device->Release();
		d3d_device = NULL;
	}
}

void CleanUpRenderTarget() {

	if (main_render_target_view) {

		main_render_target_view->Release();
		main_render_target_view = NULL;
	}
}

bool CreateDeviceD3D(HWND hwnd) {

	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd,
		sizeof(sd));
	sd.BufferCount = 2;
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.OutputWindow = hwnd;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

	UINT create_device_flags = 0;
	D3D_FEATURE_LEVEL feature_level;
	const D3D_FEATURE_LEVEL feature_level_array[2] = { D3D_FEATURE_LEVEL_11_0,
	D3D_FEATURE_LEVEL_10_0 };
	if (D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		create_device_flags,
		feature_level_array,
		2,
		D3D11_SDK_VERSION,
		&sd,
		&swap_chain,
		&d3d_device,
		&feature_level,
		&d3d_device_context) != S_OK) {

		return false;
	}

	CreateRenderTarget();
	return true;
}

void CreateRenderTarget() {

	ID3D11Texture2D* back_buffer;
	swap_chain->GetBuffer(0,
		IID_PPV_ARGS(&back_buffer));
	d3d_device->CreateRenderTargetView(back_buffer,
		NULL,
		&main_render_target_view);
	back_buffer->Release();
}

LRESULT CALLBACK WindowProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam) {

	Vtt_Client::WindowData* data;
	if (uMsg == WM_CREATE) {

		CREATESTRUCT* p_create = reinterpret_cast<CREATESTRUCT*>(lParam);
		data = reinterpret_cast<Vtt_Client::WindowData*>(p_create->lpCreateParams);
		SetWindowLongPtr(hwnd,
			GWLP_USERDATA,
			(LONG_PTR)data);
	}
	else {

		LONG_PTR ptr = GetWindowLongPtr(hwnd,
			GWLP_USERDATA);
		data = reinterpret_cast<Vtt_Client::WindowData*>(ptr);
	}

	if (ImGui_ImplWin32_WndProcHandler(hwnd,
		uMsg,
		wParam,
		lParam)) {

		return true;
	}

	switch (uMsg) {
		case WM_CLOSE: {

			// Write position and size settings into config.yaml.
			YAML::Node config;
			YAML::Node display;
			display["X"] = data->x_pos;
			display["Y"] = data->y_pos;
			display["Width"] = data->width;
			display["Height"] = data->height;
			config["Display"] = display;
			std::ofstream fout("config.yaml");
			fout << config;

			// Create and dispatch a WindowCloseEvent.
			Vtt_Api::WindowCloseEvent event;
			data->event_callback(event);

			break;
		}
		case WM_KEYDOWN: {

			if (wParam != SIZE_MINIMIZED) {

				Vtt_Api::KeyCode key_code = (lParam >> 16) & 0xff;
				uint32_t extended = (lParam >> 24) & 0x1;

				if (extended) {

					if (key_code != 0x45) {

						key_code |= 0xE000;
					}
				}
				else {

					if (key_code == 0x45) {

						key_code = 0xE11D45;
					}
					else if (key_code == 0x54) {

						key_code = 0xE037;
					}
				}
				uint16_t repeat_count = (lParam >> 0) & 0xef;
				#ifdef DEBUG
				VTT_CLIENT_INFO("KeyPressedEvent: Keycode: {0}, Repeat count: {1}",
					key_code,
					repeat_count);
				#endif // DEBUG
			}
		
			break;
		}
		case WM_MOVE: {

			data->x_pos = LOWORD(lParam);
			data->y_pos = HIWORD(lParam);
			
			break;
		}
		case WM_SIZE: {

			if (d3d_device != NULL && wParam != SIZE_MINIMIZED) {
			
				CleanUpRenderTarget();
				swap_chain->ResizeBuffers(0,
					(UINT)LOWORD(lParam),
					(UINT)HIWORD(lParam),
					DXGI_FORMAT_UNKNOWN,
					0);
				CreateRenderTarget();
			}
			data->width = LOWORD(lParam);
			data->height = HIWORD(lParam);
			break;
		}
	}

	return DefWindowProc(hwnd,
		uMsg,
		wParam,
		lParam);
}



