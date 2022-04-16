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
        List<std::reference_wrapper<const BaseConstructor>> constructors;
        List<std::reference_wrapper<const BaseProperty>> properties;
        List<std::reference_wrapper<const BaseMethod>> methods;
        List<std::reference_wrapper<const Type>> templateParams;

    public:
        TypeBuilder(const AString& _namespace, const AString& name):_namespace(_namespace), name(name), size(sizeof(T)) {}

        template<typename... ArgsT>
        inline TypeBuilder& withConstructor(const Constructor<T, ArgsT...>& constructor) {
            constructors.add(constructor);
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
            properties.add(property);
            return *this;
        }

        inline TypeBuilder& withMethod(const BaseMethod& method) {
            methods.add(method);
            return *this;
        }

        template<typename... ArgsT>
        inline TypeBuilder& withTemplateParams() {
            const Array<std::reference_wrapper<const Type>> types = { getType<ArgsT>()... };
            for (const Type& type : types)
                templateParams.add(type);
            modifiers |= TypeModifier::TEMPLATE;
            return *this;
        }

        operator Type() const {
            TypeModifier m = constructors.Empty ? modifiers | TypeModifier::ABSTRACT : modifiers;
            return Type(_namespace, name, size, m, supertype, constructors, properties, methods, templateParams);
        }
    };
}