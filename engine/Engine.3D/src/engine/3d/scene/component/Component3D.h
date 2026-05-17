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
		Component3D* parent = nullptr;
		Entity3D& owner;

	public:
		Component3D(NotNull<Entity3D> owner, World3D& world):owner(owner.ref()) {}

		virtual ~Component3D() = 0 {
		}

		inline NotNull<Entity3D> getOwner() const {
			return owner;
		}

		__declspec(property(get = getOwner)) NotNull<Entity3D> Owner;

		virtual void fixedUpdate(const Timer& timer) {}

		virtual void update(const Timer& timer) {}

		virtual void draw(RenderGroup& group) {}
	};
}
