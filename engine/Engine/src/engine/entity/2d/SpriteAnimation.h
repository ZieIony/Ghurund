#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/object/Noncopyable.h"
#include "core/object/NotNull.h"
#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class SpriteAnimation:public Noncopyable {
	private:
		struct AnimationFrame {
			IntrusivePointer<ITexture> texture;
			uint64_t durationMs;
		};

		List<AnimationFrame> frames;
		uint16_t currentFrame = 0;
		uint64_t currentTime = 0, duration = 0, frameTimeOffset = 0, prevTime = 0;
		bool loop = true;

	public:
		inline void addFrame(NotNull<ITexture> texture, uint64_t durationMs) {
			frames.add({ IntrusivePointer<ITexture>(texture.get()), durationMs });
			texture->addReference();
			duration += durationMs;
		}

		inline bool getIsLooped() const {
			return loop;
		}

		inline void setIsLooped(bool loop) {
			this->loop = loop;
		}

		__declspec(property(get = getIsLooped, put = setIsLooped)) bool IsLooped;

		void update(uint64_t time) {
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

		inline ITexture* getCurrentTexture() const {
			return frames[currentFrame].texture.get();
		}

		__declspec(property(get = getCurrentTexture)) ITexture* CurrentTexture;
	};
}
