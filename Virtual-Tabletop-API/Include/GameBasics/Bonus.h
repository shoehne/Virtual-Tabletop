#pragma once
#ifndef BONUS_H
#define BONUS_H

#include <string>

namespace Vtt_Api {

	struct BonusType {
		
		BonusType() = default;

		std::wstring bonus_type_description;
		std::wstring bonus_type_name;
		bool stacks_same = false;
		bool stacks_other = false;
	};

	class Bonus {

	public:
		Bonus() = default;
		Bonus(BonusType* type,
			int8_t value)
			: bonus_type(type), bonus_value(value) {}

		std::wstring GetBonusDescription() { return bonus_type->bonus_type_description; }
		std::wstring GetBonusName() { return bonus_type->bonus_type_name; }
		int8_t GetBonusValue() { return bonus_value; }
		void SetBonusValue(int8_t value) { bonus_value = value; }

	private:
		BonusType* bonus_type;
		int8_t bonus_value;
	};
}

#endif // !BONUS_H

