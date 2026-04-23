#pragma once

#include "AnimatorState.h"

#include "core/object/NotNull.h"
#include "core/object/RefCountedObject.h"
#include "core/state/StateMachine.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<Derived<Animation> A, Derived<AnimatorState<A>> T>
	class Animator:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<Animator<A, T>>()
				.withTemplateParams<A, T>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = Animator<A, T>::GET_TYPE();
#pragma endregion

	private:
		StateMachine stateMachine;

	public:
		inline void putState(NotNull<T> state) {
			stateMachine.putState(state.ref());
		}

		inline void putTransition(NotNull<StateTransition> transition) {
			stateMachine.putTransition(transition);
		}

		inline T* getCurrentState() const {
			return (T*)stateMachine.CurrentState;
		}

		__declspec(property(get = getCurrentState)) T* CurrentState;

		inline void jumpToState(const WString& name) {
			stateMachine.jumpToState(name);
		}

		inline void goToState(const WString& name) {
			stateMachine.goToState(name);
		}

		inline bool update() {
			return stateMachine.update();
		}

		inline void reset(const WString& name) {
			stateMachine.reset(name);
		}
	};
}
