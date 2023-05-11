#pragma once
#ifndef PLAYERCHARACTER_H
#define PLAYERCHARACTER_H

#include "EntityComponentSystem/Entity.h"

namespace Vtt_Api {

	class PlayerCharacter : public Entity {

	public:
		PlayerCharacter() = default;
		PlayerCharacter(entt::entity handle,
			EntityManager* manager);
		PlayerCharacter(PlayerCharacter& copy) = default;

	private:
		entt::entity entity_handle{ entt::null };
		EntityManager* entity_manager = nullptr;
	};
}

#endif // !PLAYERCHARACTER_H

