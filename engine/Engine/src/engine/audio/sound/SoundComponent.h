#pragma once

#include "engine/audio/sound/Sound.h"

namespace Ghurund::Engine {
	class SoundComponent {
	private:
        Sound* sound;

	public:
        inline void setSound(Sound* sound) {
            setPointer(this->sound, sound);
        }

        inline Sound* getSound() const {
            return sound;
        }

        __declspec(property(get = getSound, put = setSound)) Sound* Sound;
	};
}
