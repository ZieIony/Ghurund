#include "ghe3dpch.h"
#include "AudioSystem3D.h"

namespace Ghurund::Engine::_3D {
	AudioSystem3D::~AudioSystem3D() {
		for (auto& component : soundComponents) {
			if (!component->Sound)
				continue;
			component->Sound->stop();
		}
		if (audioListenerComponent)
			audioListenerComponent->release();
	}
	
	void AudioSystem3D::update(const Timer& timer) {
		if (!audioListenerComponent)
			return;

		for (auto& component : soundComponents) {
			if (!component->Sound)
				continue;
			component->Sound->DSPSettings = audio.calculateDSPSettings(audioListenerComponent->Listener.get(), component->Emitter.get());
		}
	}
}
