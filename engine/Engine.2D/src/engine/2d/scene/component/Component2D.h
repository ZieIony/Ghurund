#pragma once

#include "core/object/AsyncInitializable.h"
#include "core/Timer.h"
#include "engine/game/Component.h"
#include "engine/graphics/rendering/RenderGroup.h"

namespace Ghurund::Engine::_2D {
	class Entity2D;
	class World2D;

	class Component2D:public Component, public AsyncInitializable {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Component2D::GET_TYPE();
#pragma endregion

	protected:
		float drawOrder = 0;
		Component2D* parent = nullptr;
		Entity2D& owner;

	public:
		Component2D(NotNull<Entity2D> owner, World2D& world):owner(owner.ref()) {}

		virtual ~Component2D() = 0 {
		}

		inline NotNull<Entity2D> getOwner() const {
			return owner;
		}

		__declspec(property(get = getOwner)) NotNull<Entity2D> Owner;

		virtual void fixedUpdate(const Timer& timer) {}

		virtual void update(const Timer& timer) {}

		virtual void draw(RenderGroup& group) {}
	};
}
