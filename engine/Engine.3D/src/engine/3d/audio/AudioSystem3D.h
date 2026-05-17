#pragma once

#include "engine/audio/Audio.h"
#include "engine/game/system/System.h"
#include "component/SoundComponent3D.h"
#include "component/AudioListenerComponent3D.h"

namespace Ghurund::Engine::_3D {
	class AudioSystem3D:public System {
	private:
		Audio& audio;
		AudioListenerComponent3D* audioListenerComponent = nullptr;

	protected:
		virtual bool getUsesFixedUpdateInternal() const override {
			return false;
		}

	public:
		// TODO: make a proper collection
		List<IntrusivePointer<SoundComponent3D>> soundComponents;

		AudioSystem3D(Audio& audio):audio(audio) {}

		~AudioSystem3D();

		inline void setAudioListener(AudioListenerComponent3D* component) {
			setPointer(audioListenerComponent, component);
		}

		__declspec(property(put = setAudioListener)) AudioListenerComponent3D* AudioListener;

		virtual void update(const Timer& timer) override;
	};
}
