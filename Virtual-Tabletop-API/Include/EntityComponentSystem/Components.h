#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
#include <vector>

#include "Core/UUID.h"
#include "EntityComponentSystem/Property.h"
#include "GameBasics/AbilityScore.h"

namespace Vtt_Api {

	/*---
	* Base Components
	---*/

	struct DescriptionComponent {

		DescriptionComponent() = default;
		DescriptionComponent(const DescriptionComponent&) = default;
		DescriptionComponent(const std::wstring& desc) 
			: description(desc) {}

		std::wstring description;
	};

	/*---
	* The IdComponent holds a UUID to uniquely identify an Entity.
	* When creating a new Entity a new IdComponent should be added to the Entity. 
	---*/
	struct IdComponent {

		IdComponent() = default;
		IdComponent(const IdComponent&) = default;
		IdComponent(uint64_t uuid)
			: id(uuid) {}

		UUID id;
	};

	struct NpcComponent {

		NpcComponent() = default;
		NpcComponent(const NpcComponent&) = default;

		bool is_npc = true;
	};

	struct PlayerComponent {

		PlayerComponent() = default;
		PlayerComponent(const PlayerComponent&) = default;

		bool is_player = true;
	};

	struct PropertyComponent {

		PropertyComponent() = default;
		PropertyComponent(const PropertyComponent&) = default;

		std::vector<Property> properties = std::vector<Property>();
	};

	/*---
	* TagComponent's should always be used to identify an Entity by name. When creating a new Entity a new TagComponent
	* should be added to the Entity.
	---*/
	struct TagComponent {

		TagComponent() = default;
		TagComponent(const TagComponent&) = default;
		TagComponent(std::wstring& name)
			: tag(name) {}

		std::wstring tag;
	};

	struct TargetComponent {

		TargetComponent() = default;
		TargetComponent(const TargetComponent&) = default;

		bool is_target = true;
	};

	enum EntityType : uint8_t {

		ENTITY,
		NONPLAYERCHARACTER,
		PLAYERCHARACTER
	};

	struct TypeComponent {

		TypeComponent() = default;
		TypeComponent(const TypeComponent&) = default;

		EntityType entity_type;
	};
	/*---
	* Base Components End
	---*/

	/*---
	* TTRPG Components
	* Components that are exclusively used by entities that represent monsters, player characters, non player characters.
	* 
	* Currently these components are heavily leaning towards DnD/Pathfinder type d20 systems.
	* 
	* TO DO: Add components fitting other systems after doing proper research on different systems.
	---*/
	struct AbilityScoreComponent {

		AbilityScoreComponent() = default;

		std::vector<AbilityScore> ability_scores = std::vector<AbilityScore>();
	};

	struct ActionComponent {


	};

	struct BackgroundComponent {


	};

	struct ClassComponent {


	};

	struct FeatComponent {


	};

	struct InventoryComponent {

		
	};

	struct RaceComponent {


	};

	struct SkillComponent {


	};

	struct SpellbookComponent {


	};

	struct TraitComponent {


	};
	/*---
	* TTRPG Components End
	---*/

	template<typename... Component>
	struct BaseComponentGroup {

	};

	template<typename... Component>
	struct TtrpgComponentGroup {

	};

	using BaseComponents =
		BaseComponentGroup<IdComponent, PlayerComponent, PropertyComponent, TagComponent>;
}

#endif // !COMPONENTS_H

