#pragma once

#include "engine/game/action/GameAction.h"

namespace UnitTest {
	using namespace Ghurund::Engine;

	enum class TestActionState {
		IDLE, STARTED, IN_PROGRESS, FINISHED
	};

	class TestBoolAction:public GameAction<bool> {
	protected:
		virtual void onStarted() override {
			state = TestActionState::STARTED;
		}

		virtual void onInProgress(uint64_t duration) override {
			state = TestActionState::IN_PROGRESS;
		}

		virtual void onFinished(uint64_t duration) override {
			state = TestActionState::FINISHED;
		}

	public:
		TestActionState state = TestActionState::IDLE;
	};

	class TestFloatAction:public GameAction<float> {
	protected:
		virtual void onStarted() override {
			state = TestActionState::STARTED;
		}

		virtual void onInProgress(uint64_t duration) override {
			state = TestActionState::IN_PROGRESS;
		}

		virtual void onFinished(uint64_t duration) override {
			state = TestActionState::FINISHED;
		}

	public:
		TestActionState state = TestActionState::IDLE;

		TestFloatAction(float threshold = 0.01f):GameAction(threshold) {}
	};

	class TestFloatPointAction:public GameAction<FloatPoint> {
	protected:
		virtual void onStarted() override {
			state = TestActionState::STARTED;
		}

		virtual void onInProgress(uint64_t duration) override {
			state = TestActionState::IN_PROGRESS;
		}

		virtual void onFinished(uint64_t duration) override {
			state = TestActionState::FINISHED;
		}

	public:
		TestActionState state = TestActionState::IDLE;
	};
}
