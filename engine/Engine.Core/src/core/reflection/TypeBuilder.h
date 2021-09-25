#pragma once

#include "Type.h"

namespace Ghurund::Core {
    template<class T>
    class TypeBuilder {
    private:
        TypeModifier modifiers = (TypeModifier)0;
        const char* _namespace;
        const char* name;
        Type* supertype = nullptr;
        size_t size;
        List<BaseConstructor*> constructors;
        List<BaseProperty*> properties;
        List<BaseMethod*> methods;

    public:
        TypeBuilder(const char* _namespace, const char* name) {
            this->_namespace = _namespace;
            this->name = name;
            size = sizeof(T);
        }

        template<typename... ArgsT>
        TypeBuilder withConstructor(const Constructor<T, ArgsT...>& constructor) {
            constructors.add((BaseConstructor*)&constructor);
            return *this;
        }

        TypeBuilder withModifiers(TypeModifier modifiers) {
            this->modifiers = modifiers;
            return *this;
        }

        TypeBuilder withModifier(TypeModifier modifier) {
            this->modifiers = this->modifiers | modifier;
            return *this;
        }

        TypeBuilder withSupertype(const Type& supertype) {
            this->supertype = (Type*)&supertype;
            return *this;
        }

        TypeBuilder withProperty(const BaseProperty& property) {
            properties.add((BaseProperty*)&property);
            return *this;
        }

        template<typename ReturnT, typename... ArgsT>
        TypeBuilder withMethod(const Method<T, ReturnT, ArgsT...>& method) {
            methods.add((BaseTypeMethod<T>*)&method);
            return *this;
        }

        operator Type() {
            return Type(_namespace, name, size, modifiers, supertype, constructors, properties, methods);
        }
    };
}