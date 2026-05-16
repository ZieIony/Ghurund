#pragma once

#include "component/BodyComponent2D.h"
#include "engine/game/system/System.h"

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	class PhysicsSystem2D:public System {
	private:
		b2WorldId id;
		static const uint16_t subStepCount = 4;

	protected:
		virtual void onInit() override {
			b2WorldDef worldDef = b2DefaultWorldDef();
			worldDef.gravity = { 0.0f, -10.0f };
			id = b2CreateWorld(&worldDef);
		};

		inline void uninitPhysicsSystem2D() {
			b2DestroyWorld(id);
		};

		virtual void onUninit() {
			uninitPhysicsSystem2D();
		};

		virtual bool getUsesUpdateInternal() const override {
			return false;
		}

	public:
		~PhysicsSystem2D() {
			if (IsInitialized)
				uninitPhysicsSystem2D();
		}

		inline b2WorldId getId() const {
			return id;
		}

		__declspec(property(get = getId)) b2WorldId Id;

		inline void setGravity(float gravity) {
			b2World_SetGravity(id, { 0.0f, gravity });
		}

		inline float getGravity() const {
			return b2World_GetGravity(id).y;
		}

		__declspec(property(get = getGravity, put = setGravity)) float Gravity;

		virtual void fixedUpdate(const Timer& timer) {
			b2World_Step(id, timer.FixedFrameTime, subStepCount);
		}
	};
}
