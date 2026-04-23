#include "ghcpch.h"
#include "StateMachine.h"

#include "core/exception/Exceptions.h"
#include "core/logging/Logger.h"

namespace Ghurund::Core {
	void StateMachine::putTransition(NotNull<StateTransition> transition) {
		auto pointer = IntrusivePointer(transition.get());
		pointer->addReference();
		const auto& f = transitions.find(transition->From);
		if (f != transitions.end()) {
			f->value.put(transition->To, pointer);
		} else {
			Map<WString, IntrusivePointer<StateTransition>> map;
			map.put(transition->To, pointer);
			transitions.put(transition->From, map);
		}
	}

	void StateMachine::jumpToState(const WString& name) {
		auto it = states.find(name);
		if (it == states.end()) {
			auto message = std::format(_T("There is no state \"{}\"."), name);
			Logger::log(LogType::ERR0R, message.c_str());
			throw InvalidParamException("name");
		}

		auto nextState = it->value;

		if (!nextState->IsJumpable) {
			auto message = std::format(_T("State \"{}\" is not jumpable."), name);
			Logger::log(LogType::ERR0R, message.c_str());
			throw InvalidParamException("name");
		}
		currentState->leave();
		currentState = nextState.get();
		currentState->enter();
	}

	void StateMachine::goToState(const WString& name) {
		auto it = states.find(name);
		if (it == states.end()) {
			auto message = std::format(_T("There is no state \"{}\"."), name);
			Logger::log(LogType::ERR0R, message.c_str());
			throw InvalidParamException("name");
		}

		auto nextState = it->value;

		const auto& from = transitions.find(currentState->Name);
		if (from != transitions.end()) {
			const auto& to = from->value.find(name);
			if (to != from->value.end()) {
				currentState->leave();
				currentState = nextState.get();
				auto transition = to->value;
				transition->execute();
				nextState->enter();
				return;
			}
		}

		if (!nextState->IsJumpable) {
			auto message = std::format(_T("There is no transition between states \"{}\" and \"{}\", and state \"{}\" is not jumpable."), currentState->Name, name, name);
			Logger::log(LogType::ERR0R, message.c_str());
			throw InvalidParamException("name");
		}
		currentState->leave();
		currentState = nextState.get();
		currentState->enter();
	}

	bool StateMachine::update() {
		const auto& from = transitions.find(currentState->Name);
		if (from == transitions.end())
			return false;

		for (auto& entry : from->value) {
			auto transition = entry.value;
			if (transition->shouldTransition()) {
				currentState->leave();
				transition->execute();
				currentState = states.get(entry.key).get();
				currentState->enter();
				return true;
			}
		}

		return false;
	}

	void StateMachine::reset(const WString& name) {
		auto it = states.find(name);
		if (it == states.end()) {
			auto message = std::format(_T("There is no state \"{}\"."), name);
			Logger::log(LogType::ERR0R, message.c_str());
			throw InvalidParamException("name");
		}

		currentState = it->value.get();
	}
}
