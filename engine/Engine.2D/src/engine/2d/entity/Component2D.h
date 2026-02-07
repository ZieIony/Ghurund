#pragma once

#include "core/collection/List.h"
#include "engine/graphics/RenderGroup.h"

#include <cstdint>

namespace Ghurund::Engine::_2D {
	class Component2D {
	private:
		// transformation

	protected:
		virtual XMFLOAT2 getPositionInternal() const = 0;

		virtual void setPositionInternal(const XMFLOAT2& pos) = 0;

	public:
		virtual ~Component2D() = 0 {}

		inline XMFLOAT2 getPosition() const {
			return getPositionInternal();
		}

		inline void setPosition(const XMFLOAT2& pos) {
			setPositionInternal(pos);
		}

		__declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

		virtual void update(uint64_t time) {}

		virtual void draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) {}
	};

	class ComponentGroup2D:public Component2D {
	private:
		List<Component2D*> components;

	public:
		~ComponentGroup2D() {
			components.deleteItems();
		}

		inline List<Component2D*>& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) List<Component2D*>& Components;

		virtual void update(uint64_t time) override {
			for (auto& component : components)
				component->update(time);
		}

		virtual void draw(RenderGroup& group, const XMFLOAT4X4& parentTransformation) override {
			for (auto& component : components)
				component->draw(group, parentTransformation);
		}
	};
}