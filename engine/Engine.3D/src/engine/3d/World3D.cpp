#include "ghe3dpch.h"
#include "World3D.h"

#include "core/application/Application.h"
#include "engine/audio/AudioFeature.h"

namespace Ghurund::Engine::_3D {
	void World3D::onInit() {
		auto audioFeature = app.Features.get<AudioFeature>();
		if (audioFeature) {
			audioSystem.set(ghnew AudioSystem3D(audioFeature->Audio));
			systems.add(audioSystem);
		}
		physicsSystem.set(ghnew PhysicsSystem3D());
		systems.add(physicsSystem);
		systems.init();
		scene = makeIntrusive<Scene3D>(context, app.GameObjects);
	}

	void World3D::onUninit() {
		uninitWorld3D();
	}
}
