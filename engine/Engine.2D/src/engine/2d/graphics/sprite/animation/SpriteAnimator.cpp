#include "ghe2dpch.h"
#include "SpriteAnimator.h"

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::Engine::AnimatorState<Ghurund::Engine::_2D::SpriteAnimation>>() {
		static Type TYPE = TypeBuilder<Ghurund::Engine::AnimatorState<Ghurund::Engine::_2D::SpriteAnimation>>()
			.withTemplateParam<Ghurund::Engine::_2D::SpriteAnimation>();

		return TYPE;
	}
}
