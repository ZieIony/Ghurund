#pragma once

#include "engine/ecs/System.h"

#include <box2d.h>

namespace Ghurund::Engine {
	class World;
}

namespace Ghurund::Engine::_2D {
	class PhysicsSystem2D:public System {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<PhysicsSystem2D>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = PhysicsSystem2D::GET_TYPE();
#pragma endregion

	private:
		World& world;
		b2WorldId id = {};
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

		virtual void onDeinit() {
			uninitPhysicsSystem2D();
		};

	public:
		PhysicsSystem2D(World& world):world(world) {}
		
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

		virtual void fixedUpdate(const Timer& timer);

		virtual void update(const Timer& timer);
	};
}
