#pragma once

#include "engine/audio/Audio.h"
#include "engine/game/system/System.h"
#include "component/SoundComponent2D.h"
#include "component/AudioListenerComponent2D.h"

namespace Ghurund::Engine::_2D {
	class AudioSystem2D:public System {
	private:
		Audio& audio;
		AudioListenerComponent2D* audioListenerComponent = nullptr;

	protected:
		virtual bool getUsesFixedUpdateInternal() const override {
			return false;
		}

	public:
		// TODO: make a proper collection
		List<IntrusivePointer<SoundComponent2D>> soundComponents;

		AudioSystem2D(Audio& audio):audio(audio) {}

		~AudioSystem2D();

		inline void setAudioListener(AudioListenerComponent2D* component) {
			setPointer(audioListenerComponent, component);
		}

		__declspec(property(put = setAudioListener)) AudioListenerComponent2D* AudioListener;

		virtual void update(const Timer& timer) override;
	};
}
