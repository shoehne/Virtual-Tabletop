#pragma once
#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include "EntityComponentSystem/EnTT/entt.hpp"

namespace Vtt_Api {

	class Entity;

	class EntityManager {

	public:
		EntityManager() = default;

		Entity CreateEntity(const std::wstring& name = std::wstring());
		Entity CreateEntity(GameDataId id,
			const std::wstring& name = std::wstring());

	private:
		entt::registry entity_registry;

		friend class Entity;
	};
}

#endif // !ENTITYMANAGER_H
