#pragma once

#include "engine/2d/scene/component/TransformComponent2D.h"

#include "core/object/RefCountedObject.h"
#include "engine/graphics/rendering/RenderGroup.h"
#include "component/Component2DCollection.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class World2D;

	class Entity2D:public RefCountedObject, public AsyncInitializable {
	private:
		World2D& world;
		WString name;
		TransformComponent2D* transformComponent = nullptr;
		Component2DCollection components;

	protected:
		virtual CoroutineTask<void> onInit() override {
			co_await transformComponent->init();
			for(auto& component:components)
				co_await component->init();
		};

		inline void uninitEntity2D() {
			for (auto& component : components)
				component->uninit();
			transformComponent->uninit();
		};

		virtual void onUninit() {
			uninitEntity2D();
		};

	public:
		Entity2D(World2D& world):world(world) {
			transformComponent = makeComponent<TransformComponent2D>();
			components.add(transformComponent);
		}

		~Entity2D() {
			if (IsInitialized)
				uninitEntity2D();
			components.clear();
			transformComponent->release();
		}

		inline World2D& getWorld() {
			return world;
		}

		__declspec(property(get = getWorld)) World2D& World;

		inline WString& getName() {
			return name;
		}

		inline void setName(const WString& name) {
			this->name = name;
		}

		__declspec(property(get = getName, put = setName)) WString& Name;

		inline TransformComponent2D& getTransform() {
			return *transformComponent;
		}

		__declspec(property(get = getTransform)) TransformComponent2D& Transform;

		inline Component2DCollection& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) Component2DCollection& Components;

		template<Derived<Component2D> T>
		inline T* makeComponent() {
			return ghnew T(*this, world);
		}

		virtual void fixedUpdate(const Timer& timer) {
			transformComponent->fixedUpdate(timer);
			for (auto& component : components)
				component->fixedUpdate(timer);
		}

		virtual void update(const Timer& timer) {
			transformComponent->update(timer);
			for (auto& component : components)
				component->update(timer);
		}

		inline void draw(RenderGroup& group) {
			for (auto& component : components)
				component->draw(group);
		}
	};
}