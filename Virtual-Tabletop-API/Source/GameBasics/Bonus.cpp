#include "GameBasics/Bonus.h"

Vtt_Api::Bonus::Bonus(BonusType* type,
	int8_t value) {

	bonus_id = GameDataId();
	bonus_type = type;
	bonus_value = value;
}

std::wstring Vtt_Api::Bonus::GetBonusDescription() const {

	return bonus_type->bonus_type_description;
}

std::wstring Vtt_Api::Bonus::GetBonusName() const {

	return bonus_type->bonus_type_name;
}

std::wstring Vtt_Api::Bonus::GetBonusStackability() const {

	std::wstring stackability = std::wstring();

	if (bonus_type->stacks_with_same == false) {

		stackability.append(L"Multiple bonuses of this type do not stack.\n");
	}
	else {

		stackability.append(L"Multiple bonuses of this type stack with each other.\n");
	}
	if (bonus_type->stacks_with_other == false) {
	
		stackability.append(L"This bonus type does not stack with bonuses of another type.");
	}
	else {

		stackability.append(L"This bonus type does stack with bonuses of another type.");
	}

	return stackability;
}

int8_t Vtt_Api::Bonus::GetBonusValue() const {

	return bonus_value;
}