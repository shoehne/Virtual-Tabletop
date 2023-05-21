#pragma once
#ifndef GAMEEVENT_H
#define GAMEEVENT_H

#include "Events/Event.h"
#include "GameBasics/AbilityScore.h"

namespace Vtt_Api {

	class AbilityScoreEvent : public Event {

	public:
		AbilityScoreEvent(AbilityScoreModifier* modifier)
			: ability_score_mod(modifier) {}

		AbilityScoreModifier* GetAbilityScoreMod() const { return ability_score_mod; }

		EVENT_CLASS_TYPE(GAME_LOGIC_ABILITY_SCORE);
		EVENT_CLASS_CATEGORY(EVENT_CATEGORY_GAME_LOGIC);

	private:
		AbilityScoreModifier* ability_score_mod;
	};
}

#endif // !GAMEEVENT_H

