#pragma once

#include <engine/game/Component.h>
#include "engine/graphics/rendering/RenderGroup.h"

#include <cstdint>

namespace Ghurund::Engine::_2D {
	class Entity2D;

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
		Entity2D* owner = nullptr;

	public:
		virtual ~Component2D() = 0 {
		}

		inline Component2D* getParent() const {
			return parent;
		}

		inline void setParent(Component2D* parent) {
			this->parent = parent;
		}

		__declspec(property(get = getParent, put = setParent)) Component2D* Parent;

		inline Entity2D* getOwner() const {
			return owner;
		}

		inline void setOwner(Entity2D* owner) {
			this->owner = owner;
		}

		__declspec(property(get = getOwner, put = setOwner)) Entity2D* Owner;

		virtual void update(const XMFLOAT4X4& parentTransformation, uint64_t time) {}

		virtual void draw(RenderGroup& group) {}
	};
}
