#include "ghe2dpch.h"
#include "SpriteAnimation.h"

namespace Ghurund::Engine::_2D {
	const Ghurund::Core::Type& SpriteAnimation::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteAnimation>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
	
	void SpriteAnimation::update(uint64_t time) {
		int64_t dt = time - prevTime;
		prevTime = time;
		if (currentTime == duration && !loop)
			return;
		while (dt > 0) {
			auto& frame = frames[currentFrame];
			uint64_t newFrameTime = frameTimeOffset + dt;
			if (newFrameTime > frame.durationMs) {
				if (currentFrame == frames.Size - 1 && !loop) {
					currentTime = duration;
					frameTimeOffset = frame.durationMs;
					return;
				} else {
					currentFrame = (currentFrame + 1) % frames.Size;
					dt = dt - frame.durationMs + frameTimeOffset;
					frameTimeOffset = 0;
				}
			} else {
				frameTimeOffset = newFrameTime;
				return;
			}
		}
	}
}
