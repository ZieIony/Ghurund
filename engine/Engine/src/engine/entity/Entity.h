#pragma once

#include "Component.h"

#include "core/object/RefCountedObject.h"
#include <engine/graphics/RenderGroup.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class Entity:public RefCountedObject {
    private:
        WString name;
        Component* rootComponent = nullptr;

    public:
        ~Entity() {
            delete rootComponent;
        }

        inline Component& getRootComponent() {
            return *rootComponent;
        }

        inline void setRootComponent(std::unique_ptr<Component> component) {
            delete rootComponent;
            rootComponent = component.release();
        }

        __declspec(property(get = getRootComponent, put = setRootComponent)) Component& RootComponent;

        inline WString& getName() {
            return name;
        }

        inline void setName(const WString& name) {
            this->name = name;
        }

        __declspec(property(get = getName, put = setName)) WString& Name;

        inline void update(uint64_t time) {
            rootComponent->update(time);
        }

        inline void draw(RenderGroup& group) {
			rootComponent->draw(group, { 0,0 });
        }
    };
}