#include "ghe3dpch.h"
#include "AudioSystem3D.h"

#include "component/SoundComponent3D.h"

namespace Ghurund::Engine::_3D {
	AudioSystem3D::~AudioSystem3D() {
		auto viewSound = world.getView<SoundComponent3D>();
		viewSound.each([](const auto& id, auto& soundComponent) {
			if (!soundComponent.Sound)
				return;
			soundComponent.Sound->stop();
		});
		//if (audioListenerComponent)
			//audioListenerComponent.release();
	}
	
	void AudioSystem3D::update(const Timer& timer) {
		if (!audioListenerComponent)
			return;

		auto viewSound = world.getView<SoundComponent3D>();
		viewSound.each([&](const auto& id, auto& soundComponent) {
			if (!soundComponent.Sound)
				return;
			soundComponent.Sound->DSPSettings = audio.calculateDSPSettings(audioListenerComponent->Listener.get(), soundComponent.Emitter.get());
		});
	}
}
