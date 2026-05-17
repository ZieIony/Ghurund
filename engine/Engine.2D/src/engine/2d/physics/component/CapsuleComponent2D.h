#pragma once

#include "RigidBodyComponent2D.h"

#include "engine/2d/scene/component/TransformComponent2D.h"

#include <box2d.h>

namespace Ghurund::Engine::_2D {
	class CapsuleComponent2D:public RigidBodyComponent2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CapsuleComponent2D::GET_TYPE();
#pragma endregion

	private:
		b2ShapeId shapeId;
		float height = 1.0f, radius = 0.25f;

		EventHandler<TransformComponent2D> scaleChangedHandler = [&](TransformComponent2D& transform) -> bool {
			updateShape();
			return true;
		};

		inline b2Capsule makeCapsule() {
			b2Capsule capsule;
			float h = std::max(0.001f, fabs(scale.y * height));
			float r = std::min(h / 2 - 0.001f, fabs(scale.x * radius));
			capsule.radius = r;
			capsule.center1 = { 0, -h / 2 + r };
			capsule.center2 = { 0, h / 2 - r };
			return capsule;
		}

		inline void updateShape() {
			b2Capsule capsule = makeCapsule();
			b2Shape_SetCapsule(shapeId, &capsule);
		}

		void uninitCapsuleComponent2D();

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onUninit() {
			uninitCapsuleComponent2D();
			__super::onUninit();
		};

	public:
		CapsuleComponent2D(NotNull<Entity2D> owner, World2D& world):RigidBodyComponent2D(owner, world) {}
	
		~CapsuleComponent2D() {
			if (IsInitialized)
				uninitCapsuleComponent2D();
		}

		inline float getHeight() const {
			return height;
		}

		__declspec(property(get = getHeight)) float Height;

		inline float getRadius() const {
			return radius;
		}

		__declspec(property(get = getRadius)) float Radius;

		inline void setHeightRadius(float height, float radius) {
			if (this->height != height || this->radius != radius) {
				this->height = height;
				this->radius = radius;
				updateShape();
			}
		}

		virtual void update(const Timer& timer) override;
	};
}
