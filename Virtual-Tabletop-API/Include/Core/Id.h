#pragma once
#ifndef ID_H
#define ID_H

#include <stdint.h>

namespace Vtt_Api {

	class Id {

	public:
		Id() = default;
		Id(Id& copy) = default;

		operator uint64_t() const { return id; }

	protected:
		uint64_t id;
	};

	class GameDataId : public Id{

	public:
		GameDataId();
		GameDataId(const GameDataId& copy);
	};

	class UserId : public Id {

	public:
		UserId();
		UserId(const UserId& copy) = default;
	};

	class WindowId : public Id {

	public:
		WindowId();
		WindowId(const WindowId& copy) = default;
	};
}

#endif // !ID_H

