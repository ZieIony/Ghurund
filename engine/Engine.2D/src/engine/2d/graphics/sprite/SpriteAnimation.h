#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/object/NotNull.h"
#include "engine/graphics/texture/ITexture.h"
#include "engine/animation/Animator.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	struct SpriteAnimationFrame {
		IntrusivePointer<ITexture> texture;
		float duration;
	};

	// TODO: replace this with a proper collection
	using SpriteAnimationFrameList = List<SpriteAnimationFrame>;

	class SpriteAnimation:public Animation {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SpriteAnimation::GET_TYPE();
#pragma endregion

	private:
		List<SpriteAnimationFrame> frames;
		uint16_t currentFrame = 0;
		float duration = 0, frameTimeOffset = 0;

	public:
		inline SpriteAnimationFrameList& getFrames() {
			return frames;
		}

		__declspec(property(get = getFrames)) SpriteAnimationFrameList& Frames;

		inline void addFrame(NotNull<ITexture> texture, float frameDuration) {
			frames.add({ IntrusivePointer<ITexture>(texture.get()), frameDuration });
			texture->addReference();
			duration += frameDuration;
		}

		inline void addFrames(Array<NotNull<ITexture>> textures, float frameDuration) {
			for (auto& texture : textures) {
				frames.add({ IntrusivePointer<ITexture>(texture.get()), frameDuration });
				texture->addReference();
			}
			duration += frameDuration * textures.Size;
		}

		void update(float dt);

		inline ITexture* getCurrentTexture() const {
			return frames[currentFrame].texture.get();
		}

		__declspec(property(get = getCurrentTexture)) ITexture* CurrentTexture;
	};
}
