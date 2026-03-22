#pragma once

#include <engine/game/Component.h>

#include <x3daudio.h>

namespace Ghurund::Engine::_3D {
	class AudioListenerComponent3D:public Component {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = AudioListenerComponent3D::GET_TYPE();
#pragma endregion

	private:
		X3DAUDIO_LISTENER listener = {
			.OrientFront = { 0, 0, 1 },
			.OrientTop = { 0, 1, 0 }
		};

	public:
        inline void setPosition(const XMFLOAT3& pos) {
            listener.Position.x = pos.x;
            listener.Position.y = pos.y;
            listener.Position.z = pos.z;
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
            listener.OrientFront.x = dir.x;
            listener.OrientFront.y = dir.y;
            listener.OrientFront.z = dir.z;
        }

        inline XMFLOAT3 getDirection() const {
            return XMFLOAT3(listener.OrientFront.x, listener.OrientFront.y, listener.OrientFront.z);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        inline void setUp(const XMFLOAT3& up) {
            listener.OrientTop.x = up.x;
            listener.OrientTop.y = up.y;
            listener.OrientTop.z = up.z;
        }

        inline XMFLOAT3 getUp() const {
            return XMFLOAT3(listener.OrientTop.x, listener.OrientTop.y, listener.OrientTop.z);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

        const X3DAUDIO_LISTENER& getListener() const {
            return listener;
        }

        __declspec(property(get = getListener)) const X3DAUDIO_LISTENER& Listener;
    };
}
