#pragma once
#ifndef PROPERTY_H
#define PROPERTY_H

#include "Core/UUID.h"

namespace Vtt_Api {

	struct Property {

		Property() = default;
		~Property() = default;

		UUID property_id;
		std::wstring property_name = std::wstring();
	};
	
	struct BooleanProperty : public Property {

		BooleanProperty() = default;
		BooleanProperty(const BooleanProperty&) = default;
		BooleanProperty(const std::wstring name = std::wstring(),
			const bool value = false) {

			property_id = UUID();
			property_name = name;
			property_bool = value;
		}

		bool property_bool;
	};

	/*---
	* One property for all numbers to keep it simple for the user. Not every user is going to have experience with programming
	* and accessibility should be highest priority. Everybody from every background should be able to easily use the program by
	* following a simple tutorial. For now all NumberProperty's will store a float for simplicity.
	* 
	* TO DO: Optimize numbers in memory by automatically casting to appropriate types according to yet to be defined parameters.
	---*/
	struct NumberProperty : public Property {

		NumberProperty() = default;
		NumberProperty(const NumberProperty&) = default;
		NumberProperty(const std::wstring& name = std::wstring(),
			const float& value = float()) {

			property_id = UUID();
			property_name = name;
			property_float = value;
		}

		float property_float;
	};

	struct TextProperty : public Property {

		TextProperty(const std::wstring& name = std::wstring(),
			const std::wstring& text = std::wstring()) {

			property_id = UUID();
			property_name = name;
			property_text = text;
		}

		std::wstring property_text = std::wstring();
	};
}

#endif // !PROPERTY_H

