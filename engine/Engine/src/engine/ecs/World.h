#pragma once

#include "engine/application/GameApplication.h"
#include "Entity.h"

#include <entt.hpp>

namespace Ghurund::Engine {
	class World:public Initializable, public Noncopyable {
	public:
		GameApplication& app;

		World(
			GameApplication& app
		):app(app) {
		}
	};
}
