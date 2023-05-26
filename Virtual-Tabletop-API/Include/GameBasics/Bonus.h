#pragma once
#ifndef BONUS_H
#define BONUS_H

#include <string>

#include "Core/Id.h"

namespace Vtt_Api {

	struct BonusType {

		BonusType() = default;
		BonusType(bool stack_same,
			bool stack_other,
			const std::wstring& description = std::wstring(),
			const std::wstring& name = std::wstring())
			: stacks_with_same(stack_same), stacks_with_other(stack_other),
			bonus_type_description(description), bonus_type_name(name) {
		
			bonus_type_id = GameDataId();
		}
		
		std::wstring bonus_type_description;
		GameDataId bonus_type_id;
		std::wstring bonus_type_name;
		bool stacks_with_same = false;
		bool stacks_with_other = false;
	};

	class Bonus {

	public:
		Bonus() = default;
		Bonus(BonusType* type,
			int8_t value);

		std::wstring GetBonusDescription() const;
		std::wstring GetBonusName() const;
		std::wstring GetBonusStackability() const;
		int8_t GetBonusValue() const;

	private:
		GameDataId bonus_id;
		BonusType* bonus_type;
		int8_t bonus_value;
	};
}

#endif // !BONUS_H

