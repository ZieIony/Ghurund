#pragma once

#include "GameAction.h"
#include <core/math/Point.h>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class IntPointGameAction:public GameAction<IntPoint> {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<IntPointGameAction>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = IntPointGameAction::GET_TYPE();
#pragma endregion
	};
}