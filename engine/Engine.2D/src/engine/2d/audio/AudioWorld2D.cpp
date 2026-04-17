#include "ghe2dpch.h"
#include "AudioWorld2D.h"

namespace Ghurund::Engine::_2D {
	AudioWorld2D::~AudioWorld2D() {
		for (auto& component : soundComponents) {
			if (!component->Sound)
				continue;
			component->Sound->stop();
		}
		if (audioListenerComponent)
			audioListenerComponent->release();
	}
	
	void AudioWorld2D::update() {
		if (!audioListenerComponent)
			return;

		for (auto& component : soundComponents) {
			if (!component->Sound)
				continue;
			component->Sound->DSPSettings = audio.calculateDSPSettings(audioListenerComponent->Listener.get(), component->Emitter.get());
		}
	}
}
