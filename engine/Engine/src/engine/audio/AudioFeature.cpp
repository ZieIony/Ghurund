#include "ghepch.h"
#include "AudioFeature.h"

#include "core/reflection/Type.h"
#include "sound/Sound.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& AudioFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<AudioFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void AudioFeature::uninitAudioFeature() {
		resourceManager.Loaders.remove<Sound>();
		soundLoader.set(nullptr);
		audio.uninit();
	}

	CoroutineTask<void> AudioFeature::onInit() {
		audio.init();
		soundLoader = makeIntrusive<SoundLoader>(audio);
		resourceManager.Loaders.set<Sound>(soundLoader.ref());
		co_return;
	}

	void AudioFeature::onUninit() {
		uninitAudioFeature();
	}
}
