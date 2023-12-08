#include "TestPch.h"

namespace Vtt_Client {

	/*---
	* Mock window definition
	---*/
	class MockImGuiWnd : public ImGuiWindow {

		MOCK_METHOD(void, Init, (), (override));
		MOCK_METHOD(void, OnEvent, (Vtt_Api::Event& event), (override));
		MOCK_METHOD(void, OnUpdate, (), (override));
		MOCK_METHOD(void, Render, (), (override));
	};
	/*---
	* Mock window definition End
	---*/

	ImGuiWindowStack mock_wnd_stack;
	Vtt_Api::UUID mock_wnd_id;

	TEST(ImGuiWndStackTest, DoesPushWnd) {

		MockImGuiWnd* mock_wnd = new MockImGuiWnd();
		mock_wnd_id = mock_wnd->GetId();

		EXPECT_EQ(mock_wnd_stack.PushWindow(mock_wnd),
			static_cast<uint16_t>(ClientErrorCode::NoError));
	}
}