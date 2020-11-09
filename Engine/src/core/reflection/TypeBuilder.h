#pragma once

#include "Type.h"

namespace Ghurund {
    class TypeBuilder {
    private:
        BaseConstructor* constructor = nullptr;
        TypeModifier modifiers = (TypeModifier)0;
        const char* _namespace;
        const char* name;
        Type* supertype = nullptr;
        size_t size;
        List<Property*> properties;

    public:
        TypeBuilder(const char* _namespace, const char* name) {
            this->_namespace = _namespace;
            this->name = name;
            size = sizeof(Type);
        }

        TypeBuilder withConstructor(const BaseConstructor& constructor) {
            this->constructor = (BaseConstructor*)& constructor;
            return *this;
        }

        TypeBuilder withModifiers(TypeModifier modifiers) {
            this->modifiers = modifiers;
            return *this;
        }

        TypeBuilder withSupertype(const Type& supertype) {
            this->supertype = (Type*)&supertype;
            return *this;
        }

        TypeBuilder withProperty(Property& property) {
            properties.add(&property);
            return *this;
        }

        operator Type() {
            return Type(constructor, modifiers, _namespace, name, size, supertype, properties);
        }
    };
}