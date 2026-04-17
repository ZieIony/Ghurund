#pragma once

#include <DirectXMath.h>
#include <x3daudio.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;

	class SoundEmitter {
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

        X3DAUDIO_EMITTER emitter = {};

    public:
        SoundEmitter() {
            memset(&emitter, 0, sizeof(emitter));
            emitter.pCone = nullptr;
            emitter.InnerRadius = 2.0f;
            emitter.InnerRadiusAngle = X3DAUDIO_PI / 4.0f;
            emitter.ChannelRadius = 1.0f;
            emitter.pVolumeCurve = (X3DAUDIO_DISTANCE_CURVE*)&X3DAudioDefault_LinearCurve;
            emitter.CurveDistanceScaler = 5.0f;
            emitter.DopplerScaler = 1.0;
        }

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
            XMFLOAT3 out;
            XMStoreFloat3(&out, XMVector3Normalize(XMLoadFloat3(&dir)));
            emitter.OrientFront.x = out.x;
            emitter.OrientFront.y = out.y;
            emitter.OrientFront.z = out.z;
        }

        inline XMFLOAT3 getDirection() const {
            return XMFLOAT3(emitter.OrientFront.x, emitter.OrientFront.y, emitter.OrientFront.z);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        inline void setUp(const XMFLOAT3& up) {
            XMFLOAT3 out;
            XMStoreFloat3(&out, XMVector3Normalize(XMLoadFloat3(&up)));
            emitter.OrientTop.x = out.x;
            emitter.OrientTop.y = out.y;
            emitter.OrientTop.z = out.z;
        }

        inline XMFLOAT3 getUp() const {
            return XMFLOAT3(emitter.OrientTop.x, emitter.OrientTop.y, emitter.OrientTop.z);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

        inline void setChannelCount(uint32_t channels) {
            emitter.ChannelCount = channels;
            // does it matter that this array is not const?
            emitter.pChannelAzimuths = (float*)((channels <= 8) ? &channelAzimuths[channels] : nullptr);
        }

        __declspec(property(put = setChannelCount)) uint32_t ChannelCount;

        const X3DAUDIO_EMITTER& get() const {
            return emitter;
        }
	};
}
