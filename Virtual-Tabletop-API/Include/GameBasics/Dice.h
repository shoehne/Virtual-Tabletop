#pragma once
#ifndef DICE_H
#define DICE_H

#include <stdint.h>

namespace Vtt_Api {

	class Dice {

	public:
		Dice() = default;

		uint8_t RollD4();
		uint8_t RollD6();
		uint8_t RollD8();
		uint8_t RollD10();
		uint8_t RollD12();
		uint8_t RollD20();
		uint8_t RollD100();
	};
}

#endif // !DICE_H

