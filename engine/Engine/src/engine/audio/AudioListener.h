#pragma once

#include <x3daudio.h>
#include <DirectXMath.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;

	class AudioListener {
	private:
		X3DAUDIO_LISTENER listener = {};

	public:
        AudioListener() {
            // TODO: handle cone
            listener.pCone = nullptr;
        }

        inline void setPosition(const XMFLOAT3& pos) {
            listener.Position.x = pos.x;
            listener.Position.y = pos.y;
        }

        inline XMFLOAT3 getPosition() const {
            return XMFLOAT3(listener.Position.x, listener.Position.y, listener.Position.z);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 Position;

        inline void setVelocity(const XMFLOAT3& vel) {
            listener.Velocity.x = vel.x;
            listener.Velocity.y = vel.y;
            listener.Velocity.z = vel.z;
        }

        inline XMFLOAT3 getVelocity() const {
            return XMFLOAT3(listener.Position.x, listener.Velocity.y, listener.Velocity.z);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT3 Velocity;

        inline void setDirection(const XMFLOAT3& dir) {
            XMFLOAT3 out;
            XMStoreFloat3(&out, XMVector3Normalize(XMLoadFloat3(&dir)));
            listener.OrientFront.x = out.x;
            listener.OrientFront.y = out.y;
            listener.OrientFront.z = out.z;
        }

        inline XMFLOAT3 getDirection() const {
            return XMFLOAT3(listener.OrientFront.x, listener.OrientFront.y, listener.OrientFront.z);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        inline void setUp(const XMFLOAT3& up) {
            XMFLOAT3 out;
            XMStoreFloat3(&out, XMVector3Normalize(XMLoadFloat3(&up)));
            listener.OrientTop.x = out.x;
            listener.OrientTop.y = out.y;
            listener.OrientTop.z = out.z;
        }

        inline XMFLOAT3 getUp() const {
            return XMFLOAT3(listener.OrientTop.x, listener.OrientTop.y, listener.OrientTop.z);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

        const X3DAUDIO_LISTENER& get() const {
            return listener;
        }
	};
}
