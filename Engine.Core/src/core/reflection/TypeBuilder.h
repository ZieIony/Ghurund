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
        Map<AString, List<Property*>> properties;

    public:
        static const inline AString DEFAULT_GROUP = "default";

        TypeBuilder(const char* _namespace, const char* name) {
            this->_namespace = _namespace;
            this->name = name;
            size = sizeof(Type);
        }

        TypeBuilder withConstructor(const BaseConstructor& constructor) {
            this->constructor = (BaseConstructor*)&constructor;
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

        TypeBuilder withProperty(const Property& property, const AString& group = DEFAULT_GROUP) {
            size_t i = properties.indexOfKey(group);
            if (i == properties.Size)
                properties.set(group, List<Property*>());

            properties.getValue(i).add((Property*)&property);
            return *this;
        }

        operator Type() {
            return Type(constructor, modifiers, _namespace, name, size, supertype, properties);
        }
    };
}