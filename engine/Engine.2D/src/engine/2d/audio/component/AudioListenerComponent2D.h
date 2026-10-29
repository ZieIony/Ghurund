#pragma once

#include "engine/audio/AudioListener.h"

namespace Ghurund::Engine::_2D {
	class AudioListenerComponent2D {
	private:
        AudioListener listener;

	public:
        AudioListenerComponent2D() {
            memset(&listener, 0, sizeof(listener));
            listener.Direction = { 1, 0, 0 };
            listener.Up = { 0, 1, 0 };
        }

        inline void setPosition(const XMFLOAT2& pos) {
            listener.Position = { pos.x, pos.y, 0 };
        }

        inline XMFLOAT2 getPosition() const {
            return XMFLOAT2(listener.Position.x, listener.Position.y);
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

        inline void setVelocity(const XMFLOAT2& vel) {
            listener.Velocity = { vel.x, vel.y, 0 };
        }

        inline XMFLOAT2 getVelocity() const {
            return XMFLOAT2(listener.Position.x, listener.Velocity.y);
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT2 Velocity;

        inline void setDirection(const XMFLOAT2& dir) {
            listener.Direction = { dir.x, dir.y, 0 };
        }

        inline XMFLOAT2 getDirection() const {
            return XMFLOAT2(listener.Direction.x, listener.Direction.y);
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT2 Direction;

        inline void setUp(const XMFLOAT2& up) {
            listener.Up = { up.x, up.y, 0 };
        }

        inline XMFLOAT2 getUp() const {
            return XMFLOAT2(listener.Up.x, listener.Up.y);
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT2 Up;

        const AudioListener& getListener() const {
            return listener;
        }

        __declspec(property(get = getListener)) const AudioListener& Listener;
    };
}
