#include "Core/UUID.h"
#include "EntityComponentSystem/Entity.h"
#include "EntityComponentSystem/PlayerCharacter.h"

Vtt_Api::Entity Vtt_Api::EntityManager::CreateEntity(const std::wstring& name) {

	return CreateEntity(UUID(),
		name);
}

Vtt_Api::Entity Vtt_Api::EntityManager::CreateEntity(UUID id,
	const std::wstring& name) {

	Entity entity = { entity_registry.create(), this };
	entity.AddComponent<IdComponent>(uint64_t(id));
	TagComponent& entity_tag = entity.AddComponent<TagComponent>();
	entity_tag.tag = name.empty() ? L"New Entity" : name;
	entity.AddComponent<TypeComponent>(EntityType::ENTITY);

	entity_map[id] = entity;

	return entity;
}

Vtt_Api::PlayerCharacter Vtt_Api::EntityManager::CreatePlayerCharacter(const std::wstring& name) {

	return CreatePlayerCharacter(UUID(),
		name);
}

Vtt_Api::PlayerCharacter Vtt_Api::EntityManager::CreatePlayerCharacter(UUID id,
	const std::wstring& name) {

	PlayerCharacter player_character = { entity_registry.create(), this };
	player_character.AddComponent<IdComponent>(id);
	TagComponent& player_character_tag = player_character.AddComponent<TagComponent>();
	player_character_tag.tag = name.empty() ? L"New Player Character" : name;
	player_character.AddComponent<TypeComponent>(EntityType::PLAYERCHARACTER);
	player_character.AddComponent<TargetComponent>();
	player_character.AddComponent<PlayerComponent>();

	entity_map[id] = player_character;

	return player_character;
}