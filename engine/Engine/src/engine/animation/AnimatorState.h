#pragma once

#include "Animation.h"
#include "AnimationSet.h"

#include "core/object/NotNull.h"
#include <core/state/MachineState.h>
#include <core/string/String.h>
#include "core/concepts/Concepts.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<Derived<Animation> T>
	class AnimatorState:public MachineState {
	private:
		T* animation;

	public:
		AnimatorState(
			const WString& name,
			NotNull<T> animation,
			bool isJumpable = false
		):MachineState(name, isJumpable), animation(animation.get()) {
			this->animation->addReference();
		}

		~AnimatorState() {
			animation->release();
		}

		inline T* getAnimation() const {
			return animation;
		}

		__declspec(property(get = getAnimation)) T* Animation;
	};
}
