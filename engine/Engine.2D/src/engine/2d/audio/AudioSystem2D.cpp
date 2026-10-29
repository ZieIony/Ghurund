#include "ghe2dpch.h"
#include "AudioSystem2D.h"

namespace Ghurund::Engine::_2D {
	AudioSystem2D::~AudioSystem2D() {
		auto viewSound = world.getView<SoundComponent2D>();
		viewSound.each([](const auto& id, auto& soundComponent) {
			if (!soundComponent.Sound)
				return;
			soundComponent.Sound->stop();
		});
		//if (audioListenerComponent)
			//audioListenerComponent->release();
	}
	
	void AudioSystem2D::update(const Timer& timer) {
		if (!audioListenerComponent)
			return;

		auto viewSound = world.getView<SoundComponent2D>();
		viewSound.each([&](const auto& id, auto& soundComponent) {
			if (!soundComponent.Sound)
				return;
			soundComponent.Sound->DSPSettings = audio.calculateDSPSettings(audioListenerComponent->Listener.get(), soundComponent.Emitter.get());
		});
	}
}
