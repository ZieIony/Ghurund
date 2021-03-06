#pragma once

#include "core/Object.h"

namespace Ghurund::UI {
    class ObjectProperty {
    private:
        Object& owner;
        TypeProperty& property;

    public:
        ObjectProperty(Object& owner, TypeProperty& property):owner(owner), property(property) {}

        TypeProperty& getProperty() {
            return property;
        }

        __declspec(property(get = getProperty)) TypeProperty& Property;

        void get(void** value) {
            property.get(&owner, value);
        }

        void set(void* value) {
            property.set(&owner, value);
        }
    };
}