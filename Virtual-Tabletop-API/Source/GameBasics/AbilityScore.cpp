#include <cmath>

#include "Events/GameEvent.h"
#include "GameBasics/AbilityScore.h"

Vtt_Api::AbilityScore::AbilityScore(GameStatType* type,
	const std::wstring& name) {

	stat_type = type;
	if (!name.empty()) {

		stat_name = name;
	}
	else {

		stat_name = L"New Ability Score";
	}
	stat_value_total = stat_value_base;
}

Vtt_Api::AbilityScore::AbilityScore(GameStatType* type,
	int16_t mod_basis,
	int16_t mod_increment,
	const std::wstring& name) {

	stat_type = type;
	ability_score_modifier.modfier_basis = mod_basis;
	ability_score_modifier.modifier_increment = mod_increment;
	if (!name.empty()) {

		stat_name = name;
	}
	else {

		stat_name = L"New Ability Score";
	}
	stat_value_total = stat_value_base;
}

std::wstring Vtt_Api::AbilityScore::GetStatTooltip() {

	std::wstring tooltip;

	return tooltip;
}

void Vtt_Api::AbilityScore::DecrementAbilityScore(int16_t value) {

	stat_value_base -= value;
}

int8_t Vtt_Api::AbilityScore::GetAbilityScoreMod() {

	return ability_score_modifier.modifier;
}

void Vtt_Api::AbilityScore::IncrementAbilityScore(int16_t value) {

	stat_value_base += value;
}

void Vtt_Api::AbilityScore::SetAbilityModBasis(int16_t value) {

	ability_score_modifier.modfier_basis = value;
}

void Vtt_Api::AbilityScore::SetAbilityModIncrement(int8_t value) {

	ability_score_modifier.modifier_increment = value;
}

void Vtt_Api::AbilityScore::CalculateAbilityScoreMod() {

	int8_t ability_score_mod_new;
	int8_t ability_score_mod_temp = stat_value_total - ability_score_modifier.modfier_basis;
	if (ability_score_mod_temp < 0) {

		ability_score_mod_new = std::ceil(ability_score_mod_temp / ability_score_modifier.modifier_increment);
	}
	else {

		ability_score_mod_new = std::floor(ability_score_mod_temp & ability_score_modifier.modifier_increment);
	}

	/*---
	* Should the new ability score modifier be different from the old one create a AbilityScoreEvent to update
	* and recalculate everything using this specific ability score modifier.
	---*/
	if (ability_score_mod_new != ability_score_modifier.modifier) {

		ability_score_modifier.modifier = ability_score_mod_new;

		Vtt_Api::AbilityScoreEvent event(&ability_score_modifier);
		event_callback(event);
	}
}

void Vtt_Api::AbilityScore::CalculateTotalValue() {


}