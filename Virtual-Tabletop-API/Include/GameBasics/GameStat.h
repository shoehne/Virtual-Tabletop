#pragma once
#ifndef GAMESTAT_H
#define GAMESTAT_H

#include <string>
#include <vector>

#include "Events/Event.h"
#include "GameBasics/Bonus.h"

namespace Vtt_Api {

	struct GameStatProps {

		GameStatProps(const std::wstring& name = std::wstring())
			: stat_name(name) {}

		std::wstring stat_name;
		GameStatType stat_type;
	};

	enum GameStatType : uint8_t {

		None = 0,
		GENERIC,
		ABILITY_SCORE
	};

	class GameStat {

	public:
		using EventCallbackFn = std::function<void(Vtt_Api::Event&)>;

		virtual void AddStatBonus(Bonus* bonus) = 0;
		virtual void CalculateStatTotalValue() = 0;
		virtual int16_t GetStatBaseValue() = 0;
		virtual Bonus* GetStatBonus(const std::wstring& bonus_name = std::wstring()) = 0;
		virtual std::vector<Bonus*> GetStatBonuses() = 0;
		virtual std::wstring GetStatName() = 0;
		virtual GameStatType GetStatType() = 0;
		virtual int16_t GetStatTotalValue() = 0;
		virtual void SetStatBaseValue() = 0;
		virtual void SetStatName() = 0;
		/*---
		* Pointer to the creature/actor that owns this stat.
		* TO DO: Actually implement said creature/actor base class so that all NPCs, monsters, PCs etc are derived of a creature/actor.
		---*/

		Vtt_Api::Ref<GameStat> Create(const GameStatProps props = GameStatProps());
	};
}

#endif // !GAMESTAT_H

