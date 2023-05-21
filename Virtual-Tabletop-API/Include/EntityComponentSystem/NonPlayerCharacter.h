#pragma once
#ifndef NONPLAYERCHARACTER_H
#define NONPLAYERCHARACTER_H

#include "EntityComponentSystem/Entity.h"

namespace Vtt_Api {

	class NonPlayerCharacter : public Entity {

	public:
		NonPlayerCharacter() = default;
		NonPlayerCharacter(entt::entity handle,
			EntityManager* manager);
		NonPlayerCharacter(NonPlayerCharacter& copy) = default;

	private:
		entt::entity entity_handle{ entt::null };
		EntityManager* entity_manager;
	};
}

#endif // !NONPLAYERCHARACTER_H

