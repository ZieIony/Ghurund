#include "ghe2dpch.h"
#include "SpriteAnimationSet.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& _2D::SpriteAnimationSet::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteAnimationSet>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
