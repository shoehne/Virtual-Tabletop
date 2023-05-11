#pragma once
#ifndef BONUS_H
#define BONUS_H

#include "Core/UUID.h"

#include <string>
#include <unordered_map>

namespace Vtt_Api {

	struct BonusType;

	class Bonus {

	public:
		Bonus();
		Bonus(BonusType type,
			int8_t value,
			const std::wstring& description = std::wstring(),
			const std::wstring& name = std::wstring());

	private:
		std::wstring bonus_description;
		std::wstring bonus_name;
		BonusType bonus_type;
		int8_t bonus_value;
	};

	class BonusMap {
		
	public:
		BonusMap() = default;

	private:
		std::unordered_map<UUID, Bonus> bonus_map = std::unordered_map<UUID, Bonus>();
	};

	struct BonusType {
		
		
	};

	struct BonusTypeList {

		std::vector<BonusType> bonus_types;
	};
}

#endif // !BONUS_H

