#pragma once

#include "core/object/RefCountedObject.h"

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

	protected:
		virtual void onStarted(T value) {}

		virtual void onInProgress(T value, uint64_t duration) {}

		virtual void onFinished(uint64_t duration) {}

	public:
		virtual ~GameAction() = 0 {}

		void dispatchStarted(T value) {
			onStarted(value);
		}

		void dispatchInProgress(T value, uint64_t duration) {
			onInProgress(value, duration);
		}

		void dispatchFinished(uint64_t duration) {
			onFinished(duration);
		}
	};
}