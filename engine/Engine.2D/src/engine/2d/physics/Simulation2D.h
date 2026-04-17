#pragma once

#include "component/BodyComponent2D.h"

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	class Simulation2D {
	private:
		b2WorldId id;
		static const uint16_t subStepCount = 4;

	public:
		Simulation2D() {
			b2WorldDef worldDef = b2DefaultWorldDef();
			worldDef.gravity = { 0.0f, -10.0f };
			id = b2CreateWorld(&worldDef);
		}

		~Simulation2D() {
			b2DestroyWorld(id);
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

		inline void simulate(float dt) {
			b2World_Step(id, dt, subStepCount);
		}
	};
}
