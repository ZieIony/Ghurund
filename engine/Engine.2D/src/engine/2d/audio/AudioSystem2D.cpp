#include "ghe2dpch.h"
#include "AudioSystem2D.h"

namespace Ghurund::Engine::_2D {
	AudioSystem2D::~AudioSystem2D() {
		for (auto& component : soundComponents) {
			if (!component->Sound)
				continue;
			component->Sound->stop();
		}
		if (audioListenerComponent)
			audioListenerComponent->release();
	}
	
	void AudioSystem2D::update(const Timer& timer) {
		if (!audioListenerComponent)
			return;

		for (auto& component : soundComponents) {
			if (!component->Sound)
				continue;
			component->Sound->DSPSettings = audio.calculateDSPSettings(audioListenerComponent->Listener.get(), component->Emitter.get());
		}
	}
}
