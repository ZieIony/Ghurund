#pragma once

#include "GameAction.h"
#include "GameActionDispatcher.h"

namespace Ghurund::Engine {
	template<typename From, typename To, typename T>
	class TransformedGameActionDispatcher:public BaseGameActionDispatcher<From> {
	private:
		T transformer;
		GameActionDispatcher<To>* underlyingDispatcher;

	public:
		TransformedGameActionDispatcher(
			GameActionDispatcher<To>* underlyingDispatcher,
			T transformer
		):
			transformer(transformer),
			underlyingDispatcher(underlyingDispatcher) {
		}

		~TransformedGameActionDispatcher() {
			delete underlyingDispatcher;
		}

		virtual void dispatchEvent(From value, uint64_t time) override {
			underlyingDispatcher->dispatchEvent(transformer(value), time);
		}
	};
}