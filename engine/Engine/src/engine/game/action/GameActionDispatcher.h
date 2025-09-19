#pragma once

#include "GameAction.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class BaseGameActionDispatcher {
		/*
	protected:
		A* action;
		uint64_t startTime;
		T value;

	public:
		GameActionDispatcher(A* action, T initialValue = {}):action(action), value(initialValue) {}
*/
	public:
		virtual ~BaseGameActionDispatcher() = 0 {}

		virtual void dispatchEvent(T value, uint64_t time) = 0;
	};

	template<typename T>
	class GameActionDispatcher:BaseGameActionDispatcher<T> {
		/*
	protected:
		A* action;
		uint64_t startTime;
		T value;

	public:
		GameActionDispatcher(A* action, T initialValue = {}):action(action), value(initialValue) {}
*/
	};
}