#pragma once
#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

#include "GameBasics/GameStat.h"

namespace Vtt_Api {

	struct AbilityScoreModifier {

		AbilityScoreModifier() = default;

		int8_t modifier = 0;
		int8_t modfier_basis = 0;
		int8_t modifier_increment = 1;
	};

	class AbilityScore : public GameStat {

	public:
		AbilityScore() = default;
		AbilityScore(GameStatType* type,
			const std::wstring& name = std::wstring());
		AbilityScore(GameStatType* type,
			int16_t mod_basis = 0,
			int16_t mod_increment = 1,
			const std::wstring& name = std::wstring());
		virtual ~AbilityScore() = default;

		virtual std::wstring GetStatTooltip() override;

		void DecrementAbilityScore(int16_t value);
		int8_t GetAbilityScoreMod();
		void IncrementAbilityScore(int16_t value);
		void SetAbilityModBasis(int16_t value);
		void SetAbilityModIncrement(int8_t value);

	private:
		void CalculateAbilityScoreMod();
		virtual void CalculateTotalValue() override;

	private:
		AbilityScoreModifier ability_score_modifier;
	};

}

#endif // !ABILITYSCORE_H

