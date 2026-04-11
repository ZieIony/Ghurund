#pragma once

#include "engine/audio/sound/Sound.h"
#include "engine/2d/scene/component/Component2D.h"

#include <x3daudio.h>

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

        Sound* sound = nullptr;
        X3DAUDIO_EMITTER emitter = {};

	public:
        SoundComponent2D();

        ~SoundComponent2D() {
            if (sound)
                sound->release();
        }

        inline void setPosition(const XMFLOAT2& pos) {
            emitter.Position.x = pos.x;
            emitter.Position.y = pos.y;
            emitter.Position.z = 0;
        }

        inline XMFLOAT2 getPosition() const {
            return XMFLOAT2(emitter.Position.x, emitter.Position.y);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

        inline void setVelocity(const XMFLOAT2& vel) {
            emitter.Velocity.x = vel.x;
            emitter.Velocity.y = vel.y;
        }

        inline XMFLOAT2 getVelocity() const {
            return XMFLOAT2(emitter.Position.x, emitter.Velocity.y);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT2 Velocity;

        inline void setDirection(const XMFLOAT2& dir) {
            XMFLOAT2 out;
            XMStoreFloat2(&out, XMVector2Normalize(XMLoadFloat2(&dir)));
            emitter.OrientFront.x = out.x;
            emitter.OrientFront.y = out.y;
        }

        inline XMFLOAT2 getDirection() const {
            return XMFLOAT2(emitter.OrientFront.x, emitter.OrientFront.y);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT2 Direction;

        inline void setUp(const XMFLOAT2& up) {
            XMFLOAT2 out;
            XMStoreFloat2(&out, XMVector2Normalize(XMLoadFloat2(&up)));
            emitter.OrientTop.x = out.x;
            emitter.OrientTop.y = out.y;
        }

        inline XMFLOAT2 getUp() const {
            return XMFLOAT2(emitter.OrientTop.x, emitter.OrientTop.y);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT2 Up;

        inline void setSound(Sound* sound) {
            setPointer(this->sound, sound);
            if (sound) {
                emitter.ChannelCount = sound->Channels;
                // does it matter that this array is not const?
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
