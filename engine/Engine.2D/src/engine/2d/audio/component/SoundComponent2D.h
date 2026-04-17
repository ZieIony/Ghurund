#pragma once

#include "engine/audio/sound/Sound.h"
#include "engine/audio/sound/SoundEmitter.h"
#include "engine/2d/scene/component/Component2D.h"

namespace Ghurund::Engine::_2D {
	class SoundComponent2D:public Component2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SoundComponent2D::GET_TYPE();
#pragma endregion

	private:
        Sound* sound = nullptr;
        SoundEmitter emitter = {};

	public:
        SoundComponent2D(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world) {}

        ~SoundComponent2D() {
            if (sound)
                sound->release();
        }

        inline void setPosition(const XMFLOAT2& pos) {
            emitter.Position = { pos.x, pos.y, 0 };
        }

        inline XMFLOAT2 getPosition() const {
            return XMFLOAT2(emitter.Position.x, emitter.Position.y);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

        inline void setVelocity(const XMFLOAT2& vel) {
            emitter.Velocity = { vel.x, vel.y, 0 };
        }

        inline XMFLOAT2 getVelocity() const {
            return XMFLOAT2(emitter.Position.x, emitter.Velocity.y);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT2 Velocity;

        inline void setDirection(const XMFLOAT2& dir) {
            emitter.Direction = { dir.x, dir.y, 0 };
        }

        inline XMFLOAT2 getDirection() const {
            return XMFLOAT2(emitter.Direction.x, emitter.Direction.y);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT2 Direction;

        inline void setUp(const XMFLOAT2& up) {
            emitter.Up = { up.x, up.y, 0 };
        }

        inline XMFLOAT2 getUp() const {
            return XMFLOAT2(emitter.Up.x, emitter.Up.y);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT2 Up;

        inline void setSound(Sound* sound) {
            setPointer(this->sound, sound);
            if (sound)
                emitter.ChannelCount = sound->ChannelCount;
        }

        inline Sound* getSound() const {
            return sound;
        }

        __declspec(property(get = getSound, put = setSound)) Sound* Sound;

        const SoundEmitter& getEmitter() const {
            return emitter;
        }

        __declspec(property(get = getEmitter)) const SoundEmitter& Emitter;
	};
}
