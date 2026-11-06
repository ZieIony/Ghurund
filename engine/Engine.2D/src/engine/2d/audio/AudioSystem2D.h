#pragma once

#include "engine/audio/Audio.h"
#include "engine/ecs/System.h"
#include "component/AudioListenerComponent2D.h"

namespace Ghurund::Engine::_2D {
	class AudioSystem2D:public System {
	private:
		class World2D& world;
		Audio& audio;
		AudioListenerComponent2D* audioListenerComponent = nullptr;

	protected:
		virtual bool getUsesFixedUpdate_internal() const override {
			return false;
		}

	public:
		AudioSystem2D(Audio& audio, World2D& world):audio(audio), world(world) {}

		~AudioSystem2D();

		inline void setAudioListener(AudioListenerComponent2D* component) {
			audioListenerComponent = component;
		}

		__declspec(property(put = setAudioListener)) AudioListenerComponent2D* AudioListener;

		virtual void update(const Timer& timer) override;
	};
}
