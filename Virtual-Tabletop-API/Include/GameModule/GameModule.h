#pragma once
#ifndef GAMEMODULE_H
#define GAMEMODULE_H

#include <filesystem>
#include <string>

#include "Core/Core.h"
#include "Core/UUID.h"

#include "EntityComponentSystem/EnTT/entt.hpp"

namespace Vtt_Api {

	class GameModule {

	public:
		~GameModule() = default;

		operator bool() const { return is_initialised; }

	private:
		bool is_initialised = false;
		std::vector<std::filesystem::path> module_dependencies;
		std::filesystem::path module_directory;
	};
}

#endif // !GAMEMODULE_H

