#pragma once

#include "SpriteAnimation.h"

#include "engine/animation/Animator.h"

namespace Ghurund::Engine::_2D {
	using SpriteAnimator = Animator<SpriteAnimation, AnimatorState<SpriteAnimation>>;

}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::Engine::AnimatorState<Ghurund::Engine::_2D::SpriteAnimation>>();
}
