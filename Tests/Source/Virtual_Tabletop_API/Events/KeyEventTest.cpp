#include "TestPch.h"

namespace Vtt_Api {

	TEST(KeyPressedEventTest, Repeat) {

		const KeyPressedEvent test_key_press = KeyPressedEvent(KeyCode(sc_escape), true);

		EXPECT_EQ(test_key_press.GetKeyCode(), KeyCode(sc_escape));
		EXPECT_TRUE(test_key_press.IsRepeat());
	}

	TEST(KeyPressedEventTest, NoRepeat) {

		const KeyPressedEvent test_key_press = KeyPressedEvent(KeyCode(sc_escape));

		EXPECT_EQ(test_key_press.GetKeyCode(), KeyCode(sc_escape));
		EXPECT_FALSE(test_key_press.IsRepeat());
	}

	TEST(KeyReleasedEventTest, Release) {

		const KeyReleasedEvent test_key_release = KeyReleasedEvent(KeyCode(sc_escape));

		EXPECT_EQ(test_key_release.GetKeyCode(), KeyCode(sc_escape));
	}
}