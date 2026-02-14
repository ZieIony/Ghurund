#pragma once

#include "core/object/IntrusivePointer.h"
#include "core/object/NotNull.h"
#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	struct SpriteAnimationFrame {
		IntrusivePointer<ITexture> texture;
		uint64_t durationMs;
	};

	// TODO: replace this with a proper collection
	using SpriteAnimationFrameList = List<SpriteAnimationFrame>;

	class SpriteAnimation:public RefCountedObject {
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
		AString* name = nullptr;
		List<SpriteAnimationFrame> frames;
		uint16_t currentFrame = 0;
		uint64_t currentTime = 0, duration = 0, frameTimeOffset = 0, prevTime = 0;
		bool loop = true;

	public:
		~SpriteAnimation() {
			delete name;
		}

		inline const Ghurund::Core::AString* getName() const {
			return name;
		}

		inline void setName(const AString* name) {
			if (this->name)
				delete this->name;
			if (name)
				this->name = ghnew AString(*name);
		}

		inline void setName(const AString& name) {
			if (this->name)
				delete this->name;
			this->name = ghnew AString(name);
		}

		__declspec(property(get = getName, put = setName)) const Ghurund::Core::AString* Name;

		inline SpriteAnimationFrameList& getFrames() {
			return frames;
		}

		__declspec(property(get = getFrames)) SpriteAnimationFrameList& Frames;

		inline void addFrame(NotNull<ITexture> texture, uint64_t durationMs) {
			frames.add({ IntrusivePointer<ITexture>(texture.get()), durationMs });
			texture->addReference();
			duration += durationMs;
		}

		inline void addFrames(Array<NotNull<ITexture>> textures, uint64_t durationMs) {
			for (auto& texture : textures) {
				frames.add({ IntrusivePointer<ITexture>(texture.get()), durationMs });
				texture->addReference();
			}
			duration += durationMs * textures.Size;
		}

		inline bool getIsLooped() const {
			return loop;
		}

		inline void setIsLooped(bool loop) {
			this->loop = loop;
		}

		__declspec(property(get = getIsLooped, put = setIsLooped)) bool IsLooped;

		void update(uint64_t time);

		inline ITexture* getCurrentTexture() const {
			return frames[currentFrame].texture.get();
		}

		__declspec(property(get = getCurrentTexture)) ITexture* CurrentTexture;
	};
}
