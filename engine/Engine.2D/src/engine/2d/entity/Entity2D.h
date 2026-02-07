#pragma once

#include "Component2D.h"

#include "core/object/RefCountedObject.h"
#include <engine/graphics/RenderGroup.h>

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class Entity2D:public RefCountedObject {
    private:
        WString name;
        Component2D* rootComponent = nullptr;

    public:
        ~Entity2D() {
            delete rootComponent;
        }

        inline Component2D& getRootComponent() {
            return *rootComponent;
        }

        inline void setRootComponent(std::unique_ptr<Component2D> component) {
            delete rootComponent;
            rootComponent = component.release();
        }

        __declspec(property(get = getRootComponent, put = setRootComponent)) Component2D& RootComponent;

        inline WString& getName() {
            return name;
        }

        inline void setName(const WString& name) {
            this->name = name;
        }

        __declspec(property(get = getName, put = setName)) WString& Name;

        inline void setPosition(const XMFLOAT2& pos) {
            rootComponent->setPosition(pos);
        }

        inline XMFLOAT2 getPosition() const {
            return rootComponent->getPosition();
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2 Position;

        inline void update(uint64_t time) {
            rootComponent->update(time);
        }

        inline void draw(RenderGroup& group) {
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
			rootComponent->draw(group, identity);
        }
    };
}