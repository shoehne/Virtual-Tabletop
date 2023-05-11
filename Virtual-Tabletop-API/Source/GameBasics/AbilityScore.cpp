#include "GameBasics/AbilityScore.h"

Vtt_Api::AbilityScore::AbilityScore(UUID id)
	: ability_score_id(id) {}

void Vtt_Api::AbilityScore::AddScoreModifier(int8_t score,
	const std::wstring& name) {

	ability_score_modifiers.emplace_back(AbilityScoreModifier(name,
		score));
}

int8_t Vtt_Api::AbilityScore::GetBaseScore() {

	return base_score;
}

int8_t Vtt_Api::AbilityScore::GetAbilityScore() {

	int8_t ability_score = base_score;
	if (!ability_score_modifiers.empty()) {

		for (int i = 0; i < ability_score_modifiers.size(); i++) {

			ability_score += ability_score_modifiers.at(i).modifier_value;
		}
	}
	else {

		return ability_score;
	}
	
	return ability_score;
}

std::wstring Vtt_Api::AbilityScore::GetAbilityScoreDescription() {

	std::wstring description = std::wstring();
	description.append(name + L" base score: " + (wchar_t)base_score + L"\n");
	if (!ability_score_modifiers.empty()) {

		for (int i = 0; i < ability_score_modifiers.size(); i++) {

			description.append(L"\n" + ability_score_modifiers.at(i).modifier_name + L": " + 
				(wchar_t)ability_score_modifiers.at(i).modifier_value);
			if (i == ability_score_modifiers.size() - 1) {

				description.append(L"\n");
			}
		}
	}
	description.append(L"\nTotal" + name + L": " + (wchar_t)GetAbilityScore());

	return description;
}

void Vtt_Api::AbilityScore::SetBaseScore(int8_t score) {

	base_score = score;
}