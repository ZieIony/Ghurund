#pragma once

#include "engine/audio/Audio.h"
#include "engine/ecs/System.h"
#include "component/SoundComponent2D.h"
#include "component/AudioListenerComponent2D.h"
#include <engine/ecs/World.h>

namespace Ghurund::Engine::_2D {
	class AudioSystem2D:public System {
	private:
		World& world;
		Audio& audio;
		AudioListenerComponent2D* audioListenerComponent = nullptr;

	protected:
		virtual bool getUsesFixedUpdateInternal() const override {
			return false;
		}

	public:
		// TODO: make a proper collection
		List<SharedPointer<SoundComponent2D>> soundComponents;

		AudioSystem2D(Audio& audio, World& world):audio(audio), world(world) {}

		~AudioSystem2D();

		inline void setAudioListener(AudioListenerComponent2D* component) {
			audioListenerComponent = component;
		}

		__declspec(property(put = setAudioListener)) AudioListenerComponent2D* AudioListener;

		virtual void update(const Timer& timer) override;
	};
}
