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

		virtual XMFLOAT3 getPosition() const = 0;

		virtual void setPosition(const XMFLOAT3& pos) = 0;

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT3 Position;

		virtual void update(uint64_t time) {}

		virtual void draw(RenderGroup& group, const XMFLOAT3& parentPosition) {}
	};

	class ComponentGroup:public Component {
	private:
		List<Component*> components;

	public:
		inline List<Component*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) List<Component*>& Components;

		virtual void update(uint64_t time) override {
			for (auto& component : components)
				component->update(time);
		}

		virtual void draw(RenderGroup& group, const XMFLOAT3& parentPosition) override {
			for (auto& component : components)
				component->draw(group, parentPosition);
		}
	};
}