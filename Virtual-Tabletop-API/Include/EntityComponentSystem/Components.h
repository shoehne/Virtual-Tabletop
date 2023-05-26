#pragma once
#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <string>
#include <vector>

#include "Core/Id.h"

namespace Vtt_Api {

	/*---
	* Base Components
	---*/
	/*---
	* The IdComponent holds a ID to identify an Entity.
	* When creating a new Entity a new IdComponent should be added to the Entity. 
	---*/
	struct IdComponent {

		IdComponent() = default;
		IdComponent(const IdComponent&) = default;

		GameDataId game_data_id;
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

	enum class EntityType : uint8_t {

		ENTITY,
		PLAYERCHARACTER
	};

	struct TypeComponent {

		TypeComponent() = default;
		TypeComponent(const TypeComponent&) = default;

		EntityType entity_type;
	};

	template<typename... Component>
	struct BaseComponentGroup {

	};

	using BaseComponents =
		BaseComponentGroup<IdComponent, TagComponent, TypeComponent>;
	/*---
	* Base Components End
	---*/
}

#endif // !COMPONENTS_H

