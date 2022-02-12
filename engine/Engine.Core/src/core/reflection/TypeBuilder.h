#pragma once

#include "Type.h"

namespace Ghurund::Core {
    template<class T>
    class TypeBuilder {
    private:
        TypeModifier modifiers = (TypeModifier)0;
        const AString _namespace;
        const AString name;
        Type* supertype = nullptr;
        size_t size;
        List<BaseConstructor*> constructors;
        List<BaseProperty*> properties;
        List<BaseMethod*> methods;
        List<Type> templateParams;

    public:
        TypeBuilder(const AString& _namespace, const AString& name):_namespace(_namespace), name(name), size(sizeof(T)) {}

        template<typename... ArgsT>
        inline TypeBuilder& withConstructor(const Constructor<T, ArgsT...>& constructor) {
            constructors.add((BaseConstructor*)&constructor);
            return *this;
        }

        inline TypeBuilder& withModifiers(TypeModifier modifiers) {
            this->modifiers = modifiers;
            return *this;
        }

        inline TypeBuilder& withModifier(TypeModifier modifier) {
            this->modifiers = this->modifiers | modifier;
            return *this;
        }

        inline TypeBuilder& withSupertype(const Type& supertype) {
            this->supertype = (Type*)&supertype;
            return *this;
        }

        inline TypeBuilder& withProperty(const BaseProperty& property) {
            properties.add((BaseProperty*)&property);
            return *this;
        }

        template<typename ReturnT, typename... ArgsT>
        inline TypeBuilder& withMethod(const Method<T, ReturnT, ArgsT...>& method) {
            methods.add(&method);
            return *this;
        }

        inline TypeBuilder& withTemplateParams(const List<Type>& types) {
            if (!types.Empty) {
                templateParams.addAll(types);
                modifiers |= TypeModifier::TEMPLATE;
            }
            return *this;
        }

        operator Type() const {
            TypeModifier m = constructors.Empty ? modifiers | TypeModifier::ABSTRACT : modifiers;
            return Type(_namespace, name, size, m, supertype, constructors, properties, methods, templateParams);
        }
    };
}