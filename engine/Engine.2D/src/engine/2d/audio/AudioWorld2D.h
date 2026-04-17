#pragma once

#include "engine/audio/Audio.h"

#include "component/SoundComponent2D.h"
#include "component/AudioListenerComponent2D.h"

namespace Ghurund::Engine::_2D {
	class AudioWorld2D {
	private:
		Audio& audio;
		AudioListenerComponent2D* audioListenerComponent = nullptr;

	public:
		// TODO: make a proper collection
		List<IntrusivePointer<SoundComponent2D>> soundComponents;

		AudioWorld2D(Audio& audio):audio(audio) {}

		~AudioWorld2D();

		inline void setAudioListener(AudioListenerComponent2D* component) {
			setPointer(audioListenerComponent, component);
		}

		__declspec(property(put = setAudioListener)) AudioListenerComponent2D* AudioListener;

		void update();
	};
}
