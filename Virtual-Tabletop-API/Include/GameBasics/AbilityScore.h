#pragma once
#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

#include <cmath>

#include "GameBasics/GameStat.h"

namespace Vtt_Api {

	struct AbilityScoreModifier {

		AbilityScoreModifier(uint8_t base = 0,
			uint8_t step = 1)
			: ability_score_mod_base(base), ability_score_mod_step(step) {}
		void CalculateAbilityScoreMod(int16_t ability_score) {

			uint8_t ability_score_mod_temp = ability_score - ability_score_mod_base;
			if (ability_score_mod_temp > 0) {

				ability_score_modifer = std::floor(ability_score_mod_temp / ability_score_mod_step);
			}
			else if (ability_score_mod_temp < 0) {

				ability_score_modifer = std::ceil(ability_score_mod_temp / ability_score_mod_step);
			}
		}

		uint8_t ability_score_modifer;
		uint8_t ability_score_mod_base;
		uint8_t ability_score_mod_step;
	};

	class AbilityScore : public GameStat {

	public:
		AbilityScore(const GameStatProps props);

		virtual void AddStatBonus(Bonus* bonus) override;
		virtual void CalculateStatTotalValue() override;
		virtual int16_t GetStatBaseValue() override;
		virtual Bonus* GetStatBonus(const std::wstring& bonus_name = std::wstring()) override;
		virtual std::vector<Bonus*> GetStatBonuses() override;
		virtual std::wstring GetStatName() override;
		virtual GameStatType GetStatType() override;
		virtual int16_t GetStatTotalValue() override;
		virtual void SetStatBaseValue() override;
		virtual void SetStatName() override;

		uint8_t GetAbilityScoreMod();

	private:
		std::vector<Vtt_Api::Bonus*> ability_score_bonuses;
		int16_t ability_score_base_value;
		int16_t ability_score_modifier;
		std::wstring ability_score_name;
		int16_t ability_score_total_value;
		GameStatType game_stat_type;
	};
}

#endif // !ABILITYSCORE_H

