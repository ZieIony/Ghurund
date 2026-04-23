#include "ghe2dpch.h"
#include "SpriteAnimation.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SpriteAnimation::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteAnimation>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
	
	void SpriteAnimation::update(float dt) {
		if (currentFrame == frames.Size - 1 && !IsLooped)
			return;
		while (dt > 0) {
			auto& frame = frames[currentFrame];
			float newFrameTime = frameTimeOffset + dt;
			if (newFrameTime > frame.duration) {
				if (currentFrame == frames.Size - 1 && !IsLooped) {
					frameTimeOffset = frame.duration;
					return;
				} else {
					currentFrame = (currentFrame + 1) % frames.Size;
					dt = dt - frame.duration + frameTimeOffset;
					frameTimeOffset = 0;
				}
			} else {
				frameTimeOffset = newFrameTime;
				return;
			}
		}
	}
}
