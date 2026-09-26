#pragma once

#include "core/object/AsyncInitializable.h"
#include "core/Timer.h"
#include "engine/game/Component.h"
#include "engine/graphics/rendering/RenderGroup.h"

namespace Ghurund::Engine::_3D {
	class Entity3D;
	class World3D;

	class Component3D:public Component, public AsyncInitializable {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Component3D::GET_TYPE();
#pragma endregion

	protected:
		float drawOrder = 0;
		Entity3D& owner;

	public:
		Component3D(NotNull<Entity3D> owner):owner(owner.ref()) {}

		virtual ~Component3D() = 0 {
		}

		inline Entity3D& getOwner() const {
			return owner;
		}

		__declspec(property(get = getOwner)) Entity3D& Owner;

		virtual void fixedUpdate(const Timer& timer) {}

		virtual void update(const Timer& timer) {}

		virtual void queueDraw(RenderGroup& group) {}
	};
}
