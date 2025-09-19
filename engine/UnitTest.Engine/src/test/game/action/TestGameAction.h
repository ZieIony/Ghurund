#pragma once

#include "engine/game/action/FloatGameAction.h"
#include "engine/game/action/FloatPointGameAction.h"

namespace UnitTest {
	using namespace Ghurund::Engine;

	enum class TestActionState {
		IDLE, STARTED, IN_PROGRESS, FINISHED
	};

	class TestBoolAction:public GameAction<bool> {
	protected:
		virtual void onStarted(bool value) override {
			state = TestActionState::STARTED;
		}

		virtual void onInProgress(bool value, uint64_t duration) override {
			state = TestActionState::IN_PROGRESS;
		}

		virtual void onFinished(bool value, uint64_t duration) override {
			state = TestActionState::FINISHED;
		}

	public:
		TestActionState state = TestActionState::IDLE;
	};

	class TestFloatAction:public GameAction<float> {
	protected:
		virtual void onStarted(float value) override {
			state = TestActionState::STARTED;
		}

		virtual void onInProgress(float value, uint64_t duration) override {
			state = TestActionState::IN_PROGRESS;
		}

		virtual void onFinished(float value, uint64_t duration) override {
			state = TestActionState::FINISHED;
		}

	public:
		TestActionState state = TestActionState::IDLE;

		TestFloatAction(float threshold = 0.01f):GameAction(threshold) {}
	};

	class TestFloatPointAction:public GameAction<FloatPoint> {
	protected:
		virtual void onStarted(FloatPoint value) override {
			state = TestActionState::STARTED;
		}

		virtual void onInProgress(FloatPoint value, uint64_t duration) override {
			state = TestActionState::IN_PROGRESS;
		}

		virtual void onFinished(FloatPoint value, uint64_t duration) override {
			state = TestActionState::FINISHED;
		}

	public:
		TestActionState state = TestActionState::IDLE;
	};
}
