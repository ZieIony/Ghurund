#pragma once

#include "core/Event.h"
#include "Animation.h"

#include <algorithm>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class Animator {
	private:
		enum class State {
			IDLE,
			STARTING,
			RUNNING
		};

		const Animation* animation;
		uint64_t startTime = 0, currentTime;
		State state = State::IDLE;

	public:
		Event<Animator, float> progressChanged = Event<Animator, float>(*this);

		void start(const Animation& animation) {
			this->animation = &animation;
			startTime = 0;
			state = State::STARTING;
		}

		template<typename Type>
		void start(const ValueAnimation<Type>& animation, Type& variable) {
			start(animation);
			progressChanged += [this, &animation, &variable](Animator& animator, float progress) {
				variable = lerp<Type>(animation.InitialValue, animation.TargetValue, progress);
				return true;
				};
		}

		void update(uint64_t time) {
			if (state == State::IDLE)
				return;
			if (state == State::STARTING) {
				startTime = time;
				state = State::RUNNING;
			}
			currentTime = time;
			progressChanged(Progress);
			if (currentTime >= startTime + animation->Duration) {
				state = State::IDLE;
				progressChanged.clear();
			}
		}

		void finish() {
			if (state == State::IDLE)
				return;
			startTime = currentTime - animation->Duration;
			state = State::IDLE;
			progressChanged(1.0f);
			progressChanged.clear();
		}

		inline float getProgress() const {
			return animation->Interpolator->getProgress(std::max(0.0f, std::min((float)(currentTime - startTime) / animation->Duration, 1.0f)));
		}

		__declspec(property(get = getProgress)) float Progress;

		inline bool isRunning() const {
			return state != State::IDLE;
		}

		__declspec(property(get = isRunning)) bool Running;
	};
}