#include "EntityComponentSystem/Entity.h"

Vtt_Api::Entity Vtt_Api::EntityManager::CreateEntity(const std::wstring& name) {

	return CreateEntity(GameDataId(),
		name);
}

Vtt_Api::Entity Vtt_Api::EntityManager::CreateEntity(GameDataId id,
	const std::wstring& name) {

	Entity entity = { entity_registry.create(), this };
	IdComponent& entity_id = entity.AddComponent<IdComponent>();
	entity_id.game_data_id = id;
	TagComponent& entity_tag = entity.AddComponent<TagComponent>();
	if (!name.empty()) {

		entity_tag.tag = name;
	}
	else {

		entity_tag.tag = L"New Entity";
	}
	TypeComponent& entity_type = entity.AddComponent<TypeComponent>();
	entity_type.entity_type = EntityType::ENTITY;

	return entity;
}