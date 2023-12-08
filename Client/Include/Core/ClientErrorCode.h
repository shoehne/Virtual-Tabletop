#pragma once
#ifndef CLIENTERRORCODE_H
#define CLIENTERRORCODE_H

#include <stdint.h>

namespace Vtt_Client {

	/*---
	* Client specific error codes
	* No Error value = 0
	* Range: 10000 - 20000
	---*/
	enum ClientErrorCode : uint16_t {

		NoError = 0,
		/*---
		* ImGui related error codes
		* Range: 2501 - 5000
		---*/
		InvalidImGuiWnd = 2501,
		InvalidImGuiWndId = 2502
	};
}

#endif // !CLIENTERRORCODE_H

