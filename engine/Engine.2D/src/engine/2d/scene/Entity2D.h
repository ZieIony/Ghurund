#pragma once

#include "core/object/AsyncInitializable.h"
#include "component/Component2DCollection.h"
#include "engine/2d/scene/component/TransformComponent2D.h"
#include "engine/game/GameObject.h"
#include "engine/graphics/rendering/RenderGroup.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class World2D;

	class Entity2D:public GameObject, public AsyncInitializable {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Entity2D::GET_TYPE();
#pragma endregion

	private:
		World2D& world;
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
			drawGroup = DrawGroup(DrawGroup::DEFAULT_GROUP_ORDER, DrawOrder::BACK_TO_FRONT);
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

		virtual void fixedUpdate(const Timer& timer) override;

		virtual void update(const Timer& timer) override;

		virtual void draw(RenderGroup& group) override;
	};
}
