#include "ghuipch.h"
#include "Animator.h"

namespace Ghurund::UI {
	void Animator::update(uint64_t time) {
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
	
	void Animator::finish() {
		if (state == State::IDLE)
			return;
		startTime = currentTime - animation->Duration;
		state = State::IDLE;
		progressChanged(1.0f);
		progressChanged.clear();
	}
}
