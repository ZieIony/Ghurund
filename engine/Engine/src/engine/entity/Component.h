#pragma once

#include "core/collection/List.h"
#include "engine/graphics/RenderGroup.h"

#include <cstdint>

namespace Ghurund::Engine {
	class Component {
	private:
		// transformation

	public:
		virtual ~Component() = 0 {}

		virtual void update(uint64_t time) {}

		virtual void draw(RenderGroup& group, const XMFLOAT2& parentPosition) {}
	};

	class ComponentGroup:public Component {
	private:
		List<Component> components;

	public:
		inline List<Component>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) List<Component>& Components;

		virtual void update(uint64_t time) override {
			for (auto& component : components)
				component.update(time);
		}

		virtual void draw(RenderGroup& group, const XMFLOAT2& parentPosition) override {
			for (auto& component : components)
				component.draw(group, parentPosition);
		}
	};
}