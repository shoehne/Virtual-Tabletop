#include <random>
#include <unordered_map>

#include "Core/Id.h"
#include "Core/Log.h"

static std::random_device random_device;
static std::mt19937_64 mersenne_twister(random_device());

/*---
* Game Data ID
---*/
Vtt_Api::GameDataId::GameDataId() {

	std::uniform_int_distribution<uint32_t> game_data_id_distr(2049);

	id = game_data_id_distr(mersenne_twister);
}

Vtt_Api::GameDataId::GameDataId(const GameDataId& copy) {

	id = copy.id;
}
/*---
* Game Data ID End
---*/

/*---
* User ID
---*/
Vtt_Api::UserId::UserId() {

	std::uniform_int_distribution<uint32_t> user_id_distr(1024, 2048);

	id = user_id_distr(mersenne_twister);
}
/*---
* User ID End
---*/

/*---
* Window ID
---*/
Vtt_Api::WindowId::WindowId() {

	std::uniform_int_distribution<uint32_t> window_id_distr(0, 1023);

	id = window_id_distr(mersenne_twister);
}
/*---
* Window ID End
---*/