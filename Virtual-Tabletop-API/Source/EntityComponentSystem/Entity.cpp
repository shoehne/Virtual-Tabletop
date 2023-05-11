#include "EntityComponentSystem/Entity.h"

Vtt_Api::Entity::Entity(entt::entity handle,
	EntityManager* manager) {

	entity_handle = handle;
	entity_manager = manager;
}