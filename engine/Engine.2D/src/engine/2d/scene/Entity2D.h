#pragma once

#include "engine/2d/scene/component/BaseTransformComponent2D.h"

#include "core/object/RefCountedObject.h"
#include "engine/graphics/rendering/RenderGroup.h"
#include "engine/2d/IGraphics2DContext.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class World2D;

	class Entity2D:public RefCountedObject, public AsyncInitializable {
	private:
		World2D& world;
		WString name;
		BaseTransformComponent2D* rootComponent = nullptr;

	protected:
		virtual CoroutineTask<void> onInit() override {
			co_await rootComponent->init();
		};

		inline void uninitEntity2D() {
			rootComponent->uninit();
		};

		virtual void onUninit() {
			uninitEntity2D();
		};

	public:
		Entity2D(World2D& world):world(world) {}

		~Entity2D() {
			if (IsInitialized)
				uninitEntity2D();
			if (rootComponent)
				rootComponent->release();
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

		inline BaseTransformComponent2D* getRootComponent() {
			return rootComponent;
		}

		inline void setRootComponent(BaseTransformComponent2D* component) {
			setPointer(rootComponent, component);
		}

		__declspec(property(get = getRootComponent, put = setRootComponent)) BaseTransformComponent2D* RootComponent;

		template<Derived<Component2D> T>
		inline T* makeComponent() {
			return ghnew T(*this, world);
		}

		inline void update(const Timer& timer) {
			XMFLOAT4X4 identity;
			XMStoreFloat4x4(&identity, XMMatrixIdentity());
			rootComponent->update(identity, timer);
		}

		inline void draw(RenderGroup& group) {
			rootComponent->draw(group);
		}
	};
}