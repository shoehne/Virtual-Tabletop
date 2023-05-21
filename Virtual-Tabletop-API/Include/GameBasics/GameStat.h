#pragma once
#ifndef GAMESTAT_H
#define GAMESTAT_H

#include <string>
#include <vector>

#include "Events/Event.h"
#include "GameBasics/Bonus.h"

namespace Vtt_Api {

	struct GameStatType {

		GameStatType() = default;
		GameStatType(const std::wstring& name = std::wstring())
			: type_name(name) {}

		std::wstring type_name;
	};

	class GameStat {

	public:

		using EventCallBackFn = std::function<void(Vtt_Api::Event&)>;

		GameStat() = default;
		GameStat(GameStatType* type,
			const std::wstring& name = std::wstring())
			: stat_type(type), stat_name(name) {}
		virtual ~GameStat() = default;
		
		virtual std::wstring GetStatTooltip() = 0;

		void AddStatBonus(Bonus* bonus) { stat_bonuses.push_back(bonus); }
		int16_t GetBaseValue() { return stat_value_base; }
		std::wstring GetStatType() { return stat_type->type_name; }
		int16_t GetTotalValue() { return stat_value_total; }
		void SetBaseValue(int16_t value) { stat_value_base = value; }
		void SetStatName(const std::wstring& name) { stat_name = name; }
		void SetStatType(GameStatType* type) { stat_type = type; }

	protected:
		EventCallBackFn event_callback;
		std::vector<Bonus*> stat_bonuses;
		int16_t stat_value_base;
		int16_t stat_value_total;
		std::wstring stat_name;
		GameStatType* stat_type;
		
	private:
		virtual void CalculateTotalValue() = 0;
	};
}

#endif // !GAMESTAT_H

