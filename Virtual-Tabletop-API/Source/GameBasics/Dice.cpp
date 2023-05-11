#include "GameBasics/Dice.h"

#include <random>

static std::random_device random_device;
static std::mt19937_64 mersenne_twister(random_device());

uint8_t Vtt_Api::Dice::RollD4() {

	std::uniform_int_distribution<> d4_distribution(1, 4);
	
	return d4_distribution(mersenne_twister);
}

uint8_t Vtt_Api::Dice::RollD6() {

	std::uniform_int_distribution<> d6_distribution(1, 6);

	return d6_distribution(mersenne_twister);
}

uint8_t Vtt_Api::Dice::RollD8() {

	std::uniform_int_distribution<> d8_distribution(1, 8);

	return d8_distribution(mersenne_twister);
}

uint8_t Vtt_Api::Dice::RollD10() {

	std::uniform_int_distribution<> d10_distribution(1, 10);

	return d10_distribution(mersenne_twister);
}

uint8_t Vtt_Api::Dice::RollD12() {

	std::uniform_int_distribution<> d12_distribution(1, 12);

	return d12_distribution(mersenne_twister);
}

uint8_t Vtt_Api::Dice::RollD20() {

	std::uniform_int_distribution<> d20_distribution(1, 20);

	return d20_distribution(mersenne_twister);
}

uint8_t Vtt_Api::Dice::RollD100() {

	std::uniform_int_distribution<> d100_distribution(1, 100);

	return d100_distribution(mersenne_twister);
}