#pragma once

#include "core/object/AsyncInitializable.h"
#include "engine/3d/scene/component/TransformComponent3D.h"
#include "engine/game/GameObject.h"
#include "engine/graphics/rendering/RenderGroup.h"
#include "component/Component3DCollection.h"

namespace Ghurund::Engine::_3D {
    using namespace Ghurund::Core;

    class Entity3D:public GameObject, public AsyncInitializable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Entity3D::GET_TYPE();
#pragma endregion

    private:
		World3D& world;
		TransformComponent3D* transformComponent = nullptr;
		Component3DCollection components;

	protected:
		virtual CoroutineTask<void> onInit() override {
			co_await transformComponent->init();
			for (auto& component : components)
				co_await component->init();
		};

		inline void uninitEntity3D() {
			for (auto& component : components)
				component->uninit();
			transformComponent->uninit();
		};

		virtual void onUninit() {
			uninitEntity3D();
		};

	public:
		Entity3D(World3D& world):world(world) {
			transformComponent = makeComponent<TransformComponent3D>();
			components.add(transformComponent);
			drawGroup = DrawGroup(DrawGroup::DEFAULT_GROUP_ORDER, DrawOrder::BACK_TO_FRONT);
		}

		~Entity3D() {
			if (IsInitialized)
				uninitEntity3D();
			components.clear();
			transformComponent->release();
		}

		inline World3D& getWorld() {
			return world;
		}

		__declspec(property(get = getWorld)) World3D& World;

		inline TransformComponent3D& getTransform() {
			return *transformComponent;
		}

		__declspec(property(get = getTransform)) TransformComponent3D& Transform;

		inline Component3DCollection& getComponents() {
			return components;
		}

		__declspec(property(get = getComponents)) Component3DCollection& Components;

		template<Derived<Component3D> T>
		inline T* makeComponent() {
			return ghnew T(*this, world);
		}

		virtual void fixedUpdate(const Timer& timer) override;

		virtual void update(const Timer& timer) override;

		virtual void draw(RenderGroup& group) override;
    };
}
