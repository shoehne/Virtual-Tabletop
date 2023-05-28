#include "GameBasics/AbilityScore.h"

Vtt_Api::Ref<Vtt_Api::GameStat> Vtt_Api::GameStat::Create(const GameStatProps props) {

	switch (props.stat_type) {

	case GameStatType::GENERIC:

		break;
	case GameStatType::ABILITY_SCORE:
		return CreateRef<Vtt_Api::AbilityScore>(props);
	}

}