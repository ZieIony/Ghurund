#pragma once

#include "core/object/RefCountedObject.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class GameAction:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<GameAction>()
				.withSupertype(__super::GET_TYPE())
				.withTemplateParam<T>();

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = GameAction::GET_TYPE();
#pragma endregion

	public:
		virtual void onStarted(T value) {}

		virtual void onInProgress(T value, uint64_t duration) {}

		virtual void onFinished(T value, uint64_t duration) {}
	};
}