#pragma once

#include "core/Exceptions.h"
#include "core/logging/Logger.h"
#include "core/collection/List.h"
#include "core/threading/CriticalSection.h"

#include <format>

namespace Ghurund::Core {
	enum class StateMachineEdgeMode {
		REQUIRED, SAME_STATE_ALLOWED, ANY_STATE_ALLOWED
	};

	template<typename T>
	class StateMachine {
	private:
		struct S {
			std::function<void()> onStateEntered;
			std::function<void()> onStateLeave;

			S() {}

			S(std::function<void()> onStateEntered, std::function<void()> onStateLeave)
				:onStateEntered(onStateEntered), onStateLeave(onStateLeave) {}
		};

		T initialState;
		T currentState;
		Map<T, S> states;
		Map<T, Map<T, std::function<void()>>> edges;
		StateMachineEdgeMode mode;

	public:
		StateMachine(const T& initialState, StateMachineEdgeMode mode = StateMachineEdgeMode::REQUIRED):
			initialState(initialState), currentState(initialState), mode(mode) {
		}

		inline void addState(const T& state, std::function<void()> onStateEntered = nullptr, std::function<void()> onStateLeave = nullptr) {
			states.put(state, S(onStateEntered, onStateLeave));
		}

		inline void addEdge(const T& from, const T& to, std::function<void()> onStateChanged = nullptr) {
			const auto& f = edges.find(from);
			if (f != edges.end()) {
				f->value.put(to, onStateChanged);
			} else {
				Map<T, std::function<void()>> map;
				map.put(to, onStateChanged);
				edges.put(from, map);
			}
		}

		inline T getState() const {
			return currentState;
		}

		void setState(const T& state) {
			S& cs = states[currentState];
			const auto& from = edges.find(currentState);
			if (from != edges.end()) {
				const auto& to = from->value.find(state);
				if (to != from->value.end()) {
					const auto& ns = states.find(state);
					if (ns != states.end()) {
						if (cs.onStateLeave)
							cs.onStateLeave();
						currentState = state;
						auto& onStateChanged = to->value;
						if (onStateChanged)
							onStateChanged();
						if (ns->value.onStateEntered)
							ns->value.onStateEntered();
						return;
					}
				}
			}

			if (mode == StateMachineEdgeMode::SAME_STATE_ALLOWED && state == currentState) {
				if (cs.onStateLeave)
					cs.onStateLeave();
				if (cs.onStateEntered)
					cs.onStateEntered();
				return;
			}

			if (mode == StateMachineEdgeMode::ANY_STATE_ALLOWED) {
				auto ns = states.find(state);
				if (ns != states.end()) {
					if (cs.onStateLeave)
						cs.onStateLeave();
					currentState = state;
					if (ns->value.onStateEntered)
						ns->value.onStateEntered();
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