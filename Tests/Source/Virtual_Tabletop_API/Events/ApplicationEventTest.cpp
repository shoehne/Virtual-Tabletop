#include "TestPch.h"

namespace Vtt_Api {

	TEST(WindowResizeEventTest, ResizeFullHd) {

		const WindowResizeEvent test_wre(1080, 720);

		EXPECT_EQ(test_wre.GetWidth(), 1080);
		EXPECT_EQ(test_wre.GetHeight(), 720);
	}

	TEST(WindowMoveEventTest, NewPosition) {

		const WindowMoveEvent test_wme(100, 100);

		EXPECT_EQ(test_wme.GetX(), 100);
		EXPECT_EQ(test_wme.GetY(), 100);
	}
}