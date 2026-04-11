#pragma once

#include "engine/2d/scene/component/BaseTransformComponent2D.h"

#include "core/object/RefCountedObject.h"
#include "engine/graphics/rendering/RenderGroup.h"
#include "engine/2d/IGraphics2DContext.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class Entity2D:public RefCountedObject, public Initializable {
	private:
		WString name;
		BaseTransformComponent2D* rootComponent = nullptr;
		IGraphics2DContext* context = nullptr;

	protected:
		virtual void onInit() {
			rootComponent->init();
		};

		inline void uninitEntity2D() {
			rootComponent->uninit();
		};

		virtual void onUninit() {
			uninitEntity2D();
		};

	public:
		~Entity2D() {
			if (IsInitialized)
				uninitEntity2D();
			if (rootComponent)
				rootComponent->release();
		}

		inline void setContext(IGraphics2DContext* context) {
			this->context = context;
		}

		inline IGraphics2DContext* getContext() const {
			return context;
		}

		__declspec(property(get = getContext, put = setContext)) IGraphics2DContext* Context;

		inline BaseTransformComponent2D* getRootComponent() {
			return rootComponent;
		}

		inline void setRootComponent(BaseTransformComponent2D* component) {
			if (rootComponent)
				rootComponent->Owner = nullptr;
			setPointer(rootComponent, component);
			if (rootComponent)
				rootComponent->Owner = this;
		}

		__declspec(property(get = getRootComponent, put = setRootComponent)) BaseTransformComponent2D* RootComponent;

		inline WString& getName() {
			return name;
		}

		inline void setName(const WString& name) {
			this->name = name;
		}

		__declspec(property(get = getName, put = setName)) WString& Name;

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