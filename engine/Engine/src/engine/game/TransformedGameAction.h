#pragma once

#include "GameAction.h"
#include "core/object/NotNull.h"

namespace Ghurund::Engine {
	template<typename From, typename To, typename T>
	class TransformedGameAction:public GameAction<From> {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<TransformedGameAction>()
				.withSupertype(__super::GET_TYPE())
				.withTemplateParams<From, To>();

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = TransformedGameAction::GET_TYPE();
#pragma endregion

	private:
		T transformer;
		IntrusivePointer<GameAction<To>> underlyingAction;

		virtual void onStarted(From value) override {
			underlyingAction->dispatchStarted(transformer(value));
		}

		virtual void onInProgress(From value, uint64_t duration) override {
			underlyingAction->dispatchInProgress(transformer(value), duration);
		}

		virtual void onFinished(uint64_t duration) override {
			underlyingAction->dispatchFinished(duration);
		}

	public:
		TransformedGameAction(
			IntrusivePointer<GameAction<To>> underlyingAction,
			T transformer
		):
			transformer(transformer),
			underlyingAction(underlyingAction) {
		}
	};
}