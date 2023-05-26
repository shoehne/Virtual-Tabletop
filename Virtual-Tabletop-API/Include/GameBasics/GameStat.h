#pragma once
#ifndef GAMESTAT_H
#define GAMESTAT_H

#include "Events/Event.h"
#include "GameBasics/Bonus.h"

namespace Vtt_Api {

	struct GameStatProps {

		GameStatProps(const std::wstring& name = std::wstring())
			: stat_name(name) {}

		std::wstring stat_name;
	};
	
	class GameStat {

	public:
		using EventCallbackFn = std::function<void(Vtt_Api::Event&)>;

		Vtt_Api::Ref<GameStat> Create(const GameStatProps props = GameStatProps());
	};
}

#endif // !GAMESTAT_H