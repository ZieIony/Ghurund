#pragma once

#include "core/Object.h"

namespace Ghurund::UI {
    class ObjectProperty {
    private:
        Object& owner;
        Property& property;

    public:
        ObjectProperty(Object& owner, Property& property):owner(owner), property(property) {}

        Property& getProperty() {
            return property;
        }

        __declspec(property(get = getProperty)) Property& Property;

        void get(void** value) {
            property.get(&owner, value);
        }

        void set(void* value) {
            property.set(&owner, value);
        }
    };
}