#include "ghe2dpch.h"
#include "World2D.h"

#include "core/application/Application.h"
#include "engine/audio/AudioFeature.h"

namespace Ghurund::Engine::_2D {
	void World2D::onInit() {
		auto audioFeature = app.Features.get<AudioFeature>();
		if (audioFeature) {
			audioSystem.set(ghnew AudioSystem2D(audioFeature->Audio));
			systems.add(audioSystem);
		}
		physicsSystem.set(ghnew PhysicsSystem2D());
		systems.add(physicsSystem);
		systems.init();
		scene = makeIntrusive<Scene2D>(context, app.GameObjects);
	}

	void World2D::onUninit() {
		uninitWorld2D();
	}
}
