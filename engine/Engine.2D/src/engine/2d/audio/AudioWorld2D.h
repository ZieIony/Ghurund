#pragma once

#include "engine/audio/Audio.h"

#include "component/SoundComponent2D.h"
#include "component/AudioListenerComponent2D.h"

namespace Ghurund::Engine::_2D {
	class AudioWorld2D {
	private:
		Audio& audio;
		List<IntrusivePointer<SoundComponent2D>> soundComponents;
		AudioListenerComponent2D* audioListenerComponent = nullptr;

	public:
		AudioWorld2D(Audio& audio):audio(audio) {}

		~AudioWorld2D();

		inline SoundComponent2D* makeSoundComponent() {
			auto component = makeIntrusive<SoundComponent2D>();
			soundComponents.add(component);
			component->addReference();
			return component.get();
		}

		inline AudioListenerComponent2D* makeAudioListenerComponent() {
			AudioListenerComponent2D* component = ghnew AudioListenerComponent2D();
			setPointer(audioListenerComponent, component);
			return component;
		}

		void update();
	};
}
