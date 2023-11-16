#pragma once

#include "core/Exceptions.h"
#include "core/logging/Logger.h"
#include "core/collection/List.h"
#include "core/threading/CriticalSection.h"

#include <format>

namespace Ghurund::Core {
	template<typename T>
	class StateMachine {
	private:
		template<typename T>
		struct S {
			T state;
			std::function<void()> onStateEnter;
			std::function<void()> onStateLeave;

			S(T state) {
				this->state = state;
			}

			S(T state, std::function<void()> onStateEnter) {
				this->state = state;
				this->onStateEnter = onStateEnter;
			}

			S(T state, std::function<void()> onStateEnter, std::function<void()> onStateLeave) {
				this->state = state;
				this->onStateEnter = onStateEnter;
				this->onStateLeave = onStateLeave;
			}
		};

		template<typename T>
		struct E {
			T from;
			T to;
			std::function<void()> onStateChange;

			E(T from, T to) {
				this->from = from;
				this->to = to;
			}

			E(T from, T to, std::function<void()> onStateChange) {
				this->from = from;
				this->to = to;
				this->onStateChange = onStateChange;
			}
		};

		T initialState;
		S<T> currentState;
		List<S<T>> states;
		List<E<T>> edges;

		S<T>* findState(T& state) {
			for (size_t i = 0; i < states.Size; i++) {
				S<T>& s = states[i];
				if (s.state == state)
					return &s;
			}
			return nullptr;
		}

	public:
		StateMachine(T initialState): initialState(initialState), currentState(initialState) {}

		void addState(T state) {
			states.add(S<T>(state));
		}

		void addState(T state, std::function<void()> onStateEnter) {
			states.add(S<T>(state, onStateEnter));
		}

		void addState(T state, std::function<void()> onStateEnter, std::function<void()> onStateLeave) {
			states.add(S<T>(state, onStateEnter, onStateLeave));
		}

		void addEdge(T from, T to) {
			edges.add(E<T>(from, to));
		}

		void addEdge(T from, T to, std::function<void()> onStateChange) {
			edges.add(E<T>(from, to, onStateChange));
		}

		inline T getState() const {
			return currentState.state;
		}

		void setState(T state) {
			for (size_t i = 0; i < edges.Size; i++) {
				E<T>& e = edges[i];
				if (e.from == currentState.state && e.to == state) {
					if (currentState.onStateLeave != nullptr)
						currentState.onStateLeave();

					S<T>* found = findState(e.to);
					if (!found)
						break;
					currentState = *found;

					if (e.onStateChange != nullptr)
						e.onStateChange();
					if (currentState.onStateEnter != nullptr)
						currentState.onStateEnter();
					return;
				}
			}

			/*auto message = std::format(_T("No edge for specified states: {0} -> {1}\n"), currentState.state, state);
			Logger::log(LogType::WARNING, message.c_str());
			AString exMessage = convertText<tchar, char>(String(message.c_str()));
			throw InvalidParamException(exMessage.Data);*/
			throw InvalidParamException("No edge for specified states");
		}

		__declspec(property(get = getState, put = setState)) T State;

		inline void reset() {
			currentState = initialState;
		}
	};
}