#pragma once

#include "engine/audio/sound/Sound.h"
#include "engine/audio/sound/SoundEmitter.h"
#include "engine/3d/scene/component/Component3D.h"

namespace Ghurund::Engine::_3D {
	class SoundComponent3D:public Component3D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SoundComponent3D::GET_TYPE();
#pragma endregion

	private:
        Sound* sound = nullptr;
        SoundEmitter emitter = {};

	public:
        SoundComponent3D(NotNull<Entity3D> owner, World3D& world):Component3D(owner, world) {}

        ~SoundComponent3D() {
            if (sound)
                sound->release();
        }

        inline void setPosition(const XMFLOAT3& pos) {
            emitter.Position = pos;
        }

        inline XMFLOAT3 getPosition() const {
            return emitter.Position;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 Position;

        inline void setVelocity(const XMFLOAT3& vel) {
            emitter.Velocity = vel;
        }

        inline XMFLOAT3 getVelocity() const {
            return emitter.Velocity;
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT3 Velocity;

        inline void setDirection(const XMFLOAT3& dir) {
            emitter.Direction = dir;
        }

        inline XMFLOAT3 getDirection() const {
            return emitter.Direction;
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        inline void setUp(const XMFLOAT3& up) {
            emitter.Up = up;
        }

        inline XMFLOAT3 getUp() const {
            return emitter.Up;
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

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
