#pragma once
#ifndef ABILITYSCORE_H
#define ABILITYSCORE_H

#include "GameBasics/GameStat.h"

namespace Vtt_Api {

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

	private:
		std::vector<Vtt_Api::Bonus*> ability_score_bonuses;
		int16_t ability_score_base_value;
		std::wstring ability_score_name;
		int16_t ability_score_total_value;
		GameStatType game_stat_type;
	};
}

#endif // !ABILITYSCORE_H

