#pragma once

#include "engine/audio/AudioListener.h"

namespace Ghurund::Engine::_3D {
	class AudioListenerComponent3D {
	private:
		AudioListener listener;

	public:
        inline void setPosition(const XMFLOAT3& pos) {
            listener.Position = pos;
        }

        inline XMFLOAT3 getPosition() const {
            return listener.Position;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 Position;

        inline void setVelocity(const XMFLOAT3& vel) {
            listener.Velocity = vel;
        }

        inline XMFLOAT3 getVelocity() const {
            return listener.Velocity;
        }

        __declspec(property(get = getVelocity, put = setVelocity)) XMFLOAT3 Velocity;

        inline void setDirection(const XMFLOAT3& dir) {
            listener.Direction = dir;
        }

        inline XMFLOAT3 getDirection() const {
            return listener.Direction;
        }

        __declspec(property(get = getDirection, put = setDirection)) XMFLOAT3 Direction;

        inline void setUp(const XMFLOAT3& up) {
            listener.Up = up;
        }

        inline XMFLOAT3 getUp() const {
            return listener.Up;
        }

        __declspec(property(get = getUp, put = setUp)) XMFLOAT3 Up;

        const AudioListener& getListener() const {
            return listener;
        }

        __declspec(property(get = getListener)) const AudioListener& Listener;
    };
}
