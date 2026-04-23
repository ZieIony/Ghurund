#pragma once

#include "SpriteAnimation.h"

#include "engine/animation/AnimationSet.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteAnimationSet:public AnimationSet<SpriteAnimation> {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SpriteAnimationSet::GET_TYPE();
#pragma endregion

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return SpriteAnimationSet::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD | ResourceFormatOptions::CAN_SAVE);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

		// version 1 used uint32_t durationMs
		static const inline uint32_t VERSION = 2;
#pragma endregion
	};
}
