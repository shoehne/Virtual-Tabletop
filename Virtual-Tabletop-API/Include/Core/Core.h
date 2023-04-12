#pragma once
#ifndef CORE_H
#define CORE_H

#include <memory>
#include <string>

#define BIT(x) (1 << x)

#define BIND_EVENT(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

namespace Vtt_Api {

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {

		return std::make_unique<T>(std::forward<Args>(args)...);
	}

	template<typename T>
	using Ref = std::shared_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {

		return std::make_shared<T>(std::forward<Args>(args)...);
	}

	// Convert a std::string to std::wstring for some Win32 API requirements.
	#ifdef PLATFORM_WINDOWS
	#include <Windows.h>
	inline std::wstring ToWstring(std::string string) {

		int str_len = (int)string.length() + 1;
		int len = MultiByteToWideChar(CP_ACP,
			0,
			string.c_str(),
			str_len,
			0,
			0);
		wchar_t* buffer = new wchar_t[len];
		MultiByteToWideChar(CP_ACP,
			0,
			string.c_str(),
			str_len,
			buffer,
			len);

		return buffer;
	}
	#endif // PLATFORM_WINDOWS
}

#endif
