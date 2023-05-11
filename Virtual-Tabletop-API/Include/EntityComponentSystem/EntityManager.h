#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <unordered_map>

#include "Core/UUID.h"

#include "EntityComponentSystem/EnTT/entt.hpp"

namespace Vtt_Api {

	class Entity;
	class PlayerCharacter;

	class EntityManager {

	public:
		EntityManager() = default;

		Entity CreateEntity(const std::wstring& name = std::wstring()); 
		Entity CreateEntity(UUID id,
			const std::wstring& name = std::wstring());
		PlayerCharacter CreatePlayerCharacter(const std::wstring& name = std::wstring());
		PlayerCharacter CreatePlayerCharacter(UUID id,
			const std::wstring& name = std::wstring());

	private:
		std::unordered_map<UUID, entt::entity> entity_map;
		entt::registry entity_registry;

		friend class Entity;
		friend class PlayerCharacter;
	};
}

#endif // !ENTITYMANAGER_H
