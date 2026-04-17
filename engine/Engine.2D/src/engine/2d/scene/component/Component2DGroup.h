#pragma once

#include "Component2D.h"
#include "Component2DCollection.h"

#include "engine/graphics/rendering/RenderGroup.h"

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

	protected:
		virtual CoroutineTask<void> onInit() override {
			for (auto& component : components)
				co_await component->init();
		};

		inline void uninitComponent2DGroup() {
			for (auto& component : components)
				component->uninit();
		}

		virtual void onUninit() {
			uninitComponent2DGroup();
		};

	public:
		Component2DGroup(NotNull<Entity2D> owner, World2D& world):Component2D(owner, world) {}
	
		~Component2DGroup() {
			if (IsInitialized)
				uninitComponent2DGroup();
		}

		inline Component2DCollection& getComponents() {
			return components;
		}

		inline const Component2DCollection& getComponents() const {
			return components;
		}

		__declspec(property(get = getComponents)) Component2DCollection& Components;

		virtual void update(const XMFLOAT4X4& parentTransformation, const Timer& timer) override {
			for (auto& component : components)
				component->update(parentTransformation, timer);
		}

		virtual void draw(RenderGroup& group) override {
			for (auto& component : components)
				component->draw(group);
		}
	};
}
