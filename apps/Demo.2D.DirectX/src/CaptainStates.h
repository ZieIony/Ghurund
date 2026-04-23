#pragma once

#include "Captain.h"

#include <cmath>

namespace Demo {
	class CaptainSTIdleWalking:public StateTransition {
	private:
		Captain& captain;

	public:
		CaptainSTIdleWalking(Captain& captain):StateTransition(L"idle", L"walking"), captain(captain) {}

		virtual bool shouldTransition() override {
			return fabs(captain.CapsuleComponent.LinearVelocity.x) > 0.1;
		}
	};

	class CaptainSTWalkingIdle:public StateTransition {
	private:
		Captain& captain;

	public:
		CaptainSTWalkingIdle(Captain& captain):StateTransition(L"walking", L"idle"), captain(captain) {}

		virtual bool shouldTransition() override {
			return fabs(captain.CapsuleComponent.LinearVelocity.x) < 0.1;
		}
	};
}
