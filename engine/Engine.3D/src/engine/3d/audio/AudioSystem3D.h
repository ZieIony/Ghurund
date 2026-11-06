#pragma once

#include "engine/audio/Audio.h"
#include "engine/ecs/System.h"
#include "component/AudioListenerComponent3D.h"

namespace Ghurund::Engine::_3D {
	class AudioSystem3D:public System {
	private:
		class World3D& world;
		Audio& audio;
		AudioListenerComponent3D* audioListenerComponent = nullptr;

	protected:
		virtual bool getUsesFixedUpdate_internal() const override {
			return false;
		}

	public:
		AudioSystem3D(Audio& audio, World3D& world):audio(audio), world(world) {}

		~AudioSystem3D();

		inline void setAudioListener(AudioListenerComponent3D* component) {
			audioListenerComponent = component;
		}

		__declspec(property(put = setAudioListener)) AudioListenerComponent3D* AudioListener;

		virtual void update(const Timer& timer) override;
	};
}
