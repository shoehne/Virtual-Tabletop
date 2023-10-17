#include "TestPch.h"

namespace Vtt_Api {

	#ifdef PLATFORM_WINDOWS
	const std::string test_string = "Hello World!";
	const std::wstring test_wstring = L"Hello World!";

	TEST(ToWstringTest, Conversion) {

		EXPECT_EQ(ToWstring(test_string), test_wstring);
	}
	#endif // PLATFORM_WINDOWS
}