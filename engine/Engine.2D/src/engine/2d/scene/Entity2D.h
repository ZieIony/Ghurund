#pragma once

#include "engine/2d/scene/component/BaseTransformComponent2D.h"

#include "core/object/RefCountedObject.h"
#include <engine/graphics/RenderGroup.h>

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class Entity2D:public RefCountedObject {
    private:
        WString name;
        BaseTransformComponent2D* rootComponent = nullptr;

    public:
        ~Entity2D() {
            rootComponent->release();
        }

        inline BaseTransformComponent2D* getRootComponent() {
            return rootComponent;
        }

        inline void setRootComponent(BaseTransformComponent2D* component) {
            setPointer(rootComponent, component);
        }

        __declspec(property(get = getRootComponent, put = setRootComponent)) BaseTransformComponent2D* RootComponent;

        inline WString& getName() {
            return name;
        }

        inline void setName(const WString& name) {
            this->name = name;
        }

        __declspec(property(get = getName, put = setName)) WString& Name;

        inline void update(uint64_t time) {
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
            rootComponent->update(identity, time);
        }

        inline void draw(RenderGroup& group) {
			rootComponent->draw(group);
        }
    };
}