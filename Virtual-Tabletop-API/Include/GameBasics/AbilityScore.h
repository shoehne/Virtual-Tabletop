#pragma once
#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

#include <string>

#include <vector>

#include "Core/UUID.h"

namespace Vtt_Api {

	struct AbilityScoreModifier;

	class AbilityScore {

	public:
		AbilityScore(UUID id);
		~AbilityScore() = default;

		void AddScoreModifier(int8_t score = 0,
			const std::wstring& name = std::wstring());
		int8_t GetBaseScore();
		int8_t GetAbilityScore();
		std::wstring GetAbilityScoreDescription();
		void SetBaseScore(int8_t score);

	private:
		std::vector<AbilityScoreModifier> ability_score_modifiers;
		int8_t base_score = 10;
		UUID ability_score_id;
		std::wstring name = std::wstring();
	};

	struct AbilityScoreModifier {

		AbilityScoreModifier(const std::wstring& name = std::wstring(),
			int8_t modifier = 0)
			: modifier_name(name), modifier_value(modifier) {}

		std::wstring modifier_name;
		int8_t modifier_value;
	};
}

#endif // !ABILITYSCORE_H

