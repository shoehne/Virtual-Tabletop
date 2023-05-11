#include "EntityComponentSystem/PlayerCharacter.h"

Vtt_Api::PlayerCharacter::PlayerCharacter(entt::entity handle,
	EntityManager* manager)
	: entity_handle(handle), entity_manager(manager) {}