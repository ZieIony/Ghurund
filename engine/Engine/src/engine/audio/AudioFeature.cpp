#include "ghepch.h"
#include "AudioFeature.h"

#include "core/reflection/Type.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& AudioFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<AudioFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void AudioFeature::uninitAudioFeature() {
		audio.uninit();
	}

	void AudioFeature::onInit() {
		audio.init();
	}

	void AudioFeature::onUninit() {
		uninitAudioFeature();
	}
}
