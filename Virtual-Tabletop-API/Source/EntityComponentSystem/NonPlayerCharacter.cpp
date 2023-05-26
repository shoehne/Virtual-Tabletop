#include "EntityComponentSystem/NonPlayerCharacter.h"

Vtt_Api::NonPlayerCharacter::NonPlayerCharacter(entt::entity handle,
	EntityManager* manager) 
	: entity_handle(handle), entity_manager(manager) {}