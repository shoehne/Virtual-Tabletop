#include "Core/UUID.h"

#include <random>
#include <unordered_map>

static std::random_device randome_device;
static std::mt19937_64 engine(randome_device());
static std::uniform_int_distribution<uint64_t> uniform_distribution;

Vtt_Api::UUID::UUID()
	: uuid(uniform_distribution(engine)) {

}

Vtt_Api::UUID::UUID(uint64_t uuid)
	: uuid(uuid) {


}