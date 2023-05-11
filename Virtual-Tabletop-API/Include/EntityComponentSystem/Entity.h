#pragma once
#ifndef ENTITY_H
#define ENTITY_H

#include "EntityComponentSystem/Components.h"
#include "EntityComponentSystem/EntityManager.h"

namespace Vtt_Api {

	class Entity {

	public:
		Entity() = default;
		Entity(entt::entity handle,
			EntityManager* manager);
		Entity(Entity& copy) = default;
		
		template<typename T, typename... Args>
		T& AddComponent(Args&&... args) {

			T& component = entity_manager->entity_registry.emplace<T>(entity_handle, 
				std::forward<Args>(args)...);

			return component;
		}
		template<typename T, typename... Args>
		T& AddOrReplaceComponent(Args&&... args) {

			T& component = entity_manager->entity_registry.emplace_or_replace<T>(entity_handle,
				std::forward<Args>(args)...);

			return component;
		}
		template<typename T>
		T& GetComponent() {

			return entity_manager->entity_registry.get<T>(entity_handle);
		}
		template<typename T>
		bool HasAllComponents() {

			return entity_manager->entity_registry.all_of<T>(entity_handle);
		}
		template<typename T>
		bool HasAnyComponent() {

			return entity_manager->entity_registry.any_of<T>(entity_handle);
		}
		template<typename T>
		void RemoveComponent() {

			entity_manager->entity_registry.remove<T>(entity_handle);
		}

		UUID GetId() {

			return GetComponent<IdComponent>().id;
		}

		operator bool() const { return entity_handle != entt::null; }
		operator entt::entity() const { return entity_handle; }

	private:
		entt::entity entity_handle{ entt::null };
		EntityManager* entity_manager = nullptr;
	};
}

#endif // !ENTITY_H
