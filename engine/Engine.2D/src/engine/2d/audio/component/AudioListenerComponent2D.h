#pragma once

#include <engine/2d/scene/component/Component2D.h>

#include <x3daudio.h>

namespace Ghurund::Engine::_2D {
	class AudioListenerComponent2D:public Component2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = AudioListenerComponent2D::GET_TYPE();
#pragma endregion

	private:
		X3DAUDIO_LISTENER listener = {};

	public:
		AudioListenerComponent2D();

        inline void setPosition(const XMFLOAT2& pos) {
            listener.Position.x = pos.x;
            listener.Position.y = pos.y;
        }

        inline XMFLOAT2 getPosition() const {
            return XMFLOAT2(listener.Position.x, listener.Position.y);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

        inline void setVelocity(const XMFLOAT2& vel) {
            listener.Velocity.x = vel.x;
            listener.Velocity.y = vel.y;
        }

        inline XMFLOAT2 getVelocity() const {
            return XMFLOAT2(listener.Position.x, listener.Velocity.y);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT2 Velocity;

        inline void setDirection(const XMFLOAT2& dir) {
            XMFLOAT2 out;
            XMStoreFloat2(&out, XMVector2Normalize(XMLoadFloat2(&dir)));
            listener.OrientFront.x = out.x;
            listener.OrientFront.y = out.y;
        }

        inline XMFLOAT2 getDirection() const {
            return XMFLOAT2(listener.OrientFront.x, listener.OrientFront.y);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT2 Direction;

        inline void setUp(const XMFLOAT2& up) {
            XMFLOAT2 out;
            XMStoreFloat2(&out, XMVector2Normalize(XMLoadFloat2(&up)));
            listener.OrientTop.x = out.x;
            listener.OrientTop.y = out.y;
        }

        inline XMFLOAT2 getUp() const {
            return XMFLOAT2(listener.OrientTop.x, listener.OrientTop.y);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT2 Up;

        const X3DAUDIO_LISTENER& getListener() const {
            return listener;
        }

        __declspec(property(get = getListener)) const X3DAUDIO_LISTENER& Listener;
    };
}
