#pragma once

#include "Component2D.h"
#include "Component2DCollection.h"

#include "engine/graphics/RenderGroup.h"

#include <cstdint>

namespace Ghurund::Engine::_2D {
	class Component2DGroup:public Component2D {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Component2DGroup::GET_TYPE();
#pragma endregion

	private:
		Component2DCollection components = *this;

	public:
		inline Component2DCollection& getComponents() {
			return components;
		}

		inline const Component2DCollection& getComponents() const {
			return components;
		}

		__declspec(property(get = getComponents)) Component2DCollection& Components;

		virtual void update(const XMFLOAT4X4& parentTransformation, uint64_t time) override {
			for (auto& component : components)
				component->update(parentTransformation, time);
		}

		virtual void draw(RenderGroup& group) override {
			for (auto& component : components)
				component->draw(group);
		}
	};
}
