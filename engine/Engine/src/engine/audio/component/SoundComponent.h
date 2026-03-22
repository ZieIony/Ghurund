#pragma once

#include <engine/audio/sound/Sound.h>
#include <engine/game/Component.h>

namespace Ghurund::Engine {
	class SoundComponent:public Component {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SoundComponent::GET_TYPE();
#pragma endregion

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
