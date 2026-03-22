#pragma once

#include <engine/audio/sound/Sound.h>
#include <engine/game/Component.h>

#include <x3daudio.h>

namespace Ghurund::Engine::_3D {
	class SoundComponent3D:public Component {
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
        static const inline float LEFT_AZIMUTH = 3 * X3DAUDIO_PI / 2;
        static const inline float RIGHT_AZIMUTH = X3DAUDIO_PI / 2;
        static const inline float FRONT_LEFT_AZIMUTH = 7 * X3DAUDIO_PI / 4;
        static const inline float FRONT_RIGHT_AZIMUTH = X3DAUDIO_PI / 4;
        static const inline float FRONT_CENTER_AZIMUTH = 0.0f;
        static const inline float LOW_FREQUENCY_AZIMUTH = X3DAUDIO_2PI;
        static const inline float BACK_LEFT_AZIMUTH = 5 * X3DAUDIO_PI / 4;
        static const inline float BACK_RIGHT_AZIMUTH = 3 * X3DAUDIO_PI / 4;
        static const inline float BACK_CENTER_AZIMUTH = X3DAUDIO_PI;

        static const inline float channelAzimuths[9][8] = {
            /* 0 */   { 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f },
            /* 1 */   { 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f },
            /* 2 */   { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f },
            /* 2.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, LOW_FREQUENCY_AZIMUTH, 0.f, 0.f, 0.f, 0.f, 0.f },
            /* 4.0 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, 0.f, 0.f, 0.f, 0.f },
            /* 4.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, 0.f, 0.f, 0.f },
            /* 5.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, FRONT_CENTER_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, 0.f, 0.f },
            /* 6.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, FRONT_CENTER_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, BACK_CENTER_AZIMUTH, 0.f },
            /* 7.1 */ { FRONT_LEFT_AZIMUTH, FRONT_RIGHT_AZIMUTH, FRONT_CENTER_AZIMUTH, LOW_FREQUENCY_AZIMUTH, BACK_LEFT_AZIMUTH, BACK_RIGHT_AZIMUTH, LEFT_AZIMUTH, RIGHT_AZIMUTH }
        };

        Sound* sound;
        X3DAUDIO_EMITTER emitter = {
            .ChannelRadius = 1.0f,
            .CurveDistanceScaler = 1.0f,
            .DopplerScaler = 1.0f
        };

	public:
        inline void setPosition(const XMFLOAT3& pos) {
            emitter.Position.x = pos.x;
            emitter.Position.y = pos.y;
            emitter.Position.z = pos.z;
        }

        inline XMFLOAT3 getPosition() const {
            return XMFLOAT3(emitter.Position.x, emitter.Position.y, emitter.Position.z);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 Position;

        inline void setVelocity(const XMFLOAT3& vel) {
            emitter.Velocity.x = vel.x;
            emitter.Velocity.y = vel.y;
            emitter.Velocity.z = vel.z;
        }

        inline XMFLOAT3 getVelocity() const {
            return XMFLOAT3(emitter.Position.x, emitter.Velocity.y, emitter.Velocity.z);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT3 Velocity;

        inline void setDirection(const XMFLOAT3& dir) {
            emitter.OrientFront.x = dir.x;
            emitter.OrientFront.y = dir.y;
            emitter.OrientFront.z = dir.z;
        }

        inline XMFLOAT3 getDirection() const {
            return XMFLOAT3(emitter.OrientFront.x, emitter.OrientFront.y, emitter.OrientFront.z);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        inline void setUp(const XMFLOAT3& up) {
            emitter.OrientTop.x = up.x;
            emitter.OrientTop.y = up.y;
            emitter.OrientTop.z = up.z;
        }

        inline XMFLOAT3 getUp() const {
            return XMFLOAT3(emitter.OrientTop.x, emitter.OrientTop.y, emitter.OrientTop.z);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

        inline void setSound(Sound* sound) {
            setPointer(this->sound, sound);
            if (sound) {
                emitter.ChannelCount = sound->Channels;
                // does this matter that this array is not const?
                emitter.pChannelAzimuths = (float*)((sound->Channels <= 8) ? &channelAzimuths[sound->Channels] : nullptr);
            }
        }

        inline Sound* getSound() const {
            return sound;
        }

        __declspec(property(get = getSound, put = setSound)) Sound* Sound;

        const X3DAUDIO_EMITTER& getEmitter() const {
            return emitter;
        }

        __declspec(property(get = getEmitter)) const X3DAUDIO_EMITTER& Emitter;
	};
}
