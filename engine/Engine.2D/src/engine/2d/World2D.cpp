#include "ghe2dpch.h"
#include "World2D.h"

#include "core/application/Application.h"
#include "engine/audio/AudioFeature.h"

namespace Ghurund::Engine::_2D {
	void World2D::onInit() {
		auto audioFeature = app.Features.get<AudioFeature>();
		if (audioFeature) {
			audioSystem.set(ghnew AudioSystem2D(audioFeature->Audio, *this));
			systems.add(audioSystem);
		}
		physicsSystem.set(ghnew PhysicsSystem2D(*this));
		systems.add(physicsSystem);
		scene = makeIntrusive<Scene2D>();
	}

	void World2D::onDeinit() {
		uninitWorld2D();
	}
}
