#pragma once

#include "Constructor.h"
#include "BaseProperty.h"
#include "Method.h"
#include "TypeModifier.h"
#include "core/collection/List.h"
#include "core/string/String.h"

namespace Ghurund::Core {
    class Type:public NamedObject<char> {
    private:
        const TypeModifier modifiers;
        const AString _namespace;
        const size_t size;
        const Type* supertype;
        const List<BaseConstructor*> constructors;
        const List<BaseProperty*> properties;
        const List<BaseMethod*> methods;

        static List<Type>& getTypes() {
            static List<Type> types;
            return types;
        }

    public:
        Type(const char* name, size_t size): NamedObject<char>(name), modifiers((TypeModifier)0), size(size) {
            getTypes().add(*this);
        }

        Type(const char* _namespace, const char* name, size_t size):
            NamedObject<char>(name),
            _namespace(_namespace),
            modifiers((TypeModifier)0),
            size(size)
        {
            getTypes().add(*this);
        }

        Type(
            const AString& _namespace,
            const AString& name,
            size_t size,
            TypeModifier modifiers,
            Type* supertype,
            List<BaseConstructor*>& constructors,
            List<BaseProperty*>& properties,
            List<BaseMethod*>& methods
        ):
            NamedObject<char>(name),
            constructors(constructors),
            modifiers(modifiers),
            _namespace(_namespace),
            size(size),
            supertype(supertype),
            properties(properties),
            methods(methods)
        {
            getTypes().add(*this);
        }

        static const Type* fromName(const char* _namespace, const char* name) {
            for (const Type& type : TYPES) {
                if (type.Namespace == _namespace && type.Name == name)
                    return &type;
            }
            return nullptr;
        }

        const List<BaseConstructor*> getConstructors() const {
            return constructors;
        }

        __declspec(property(get = getConstructors)) List<BaseConstructor*>& Constructors;

        const AString& getNamespace() const {
            return _namespace;
        }

        __declspec(property(get = getNamespace)) const AString& Namespace;

        const size_t getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) size_t Size;

        const Type* getSupertype() const {
            return supertype;
        }

        __declspec(property(get = getSupertype)) const Type* Supertype;

        const TypeModifier getModifiers() const {
            return modifiers;
        }

        __declspec(property(get = getModifiers)) const TypeModifier Modifiers;

        const List<BaseProperty*>& getProperties() const {
            return properties;
        }

        __declspec(property(get = getProperties)) const List<BaseProperty*>& Properties;

        const List<BaseMethod*>& getMethods() const {
            return methods;
        }

        __declspec(property(get = getMethods)) const List<BaseMethod*>& Methods;

        bool operator==(const Type& type) const {
            return _namespace == type._namespace && __super::operator==(type);
        }

        inline static const List<Type>& TYPES = getTypes();

        bool isOrExtends(const Type& type) const {
            Type* st = (Type*)this;
            while (st != nullptr) {
                if (*st == type)
                    return true;
                st = (Type*)st->Supertype;
            }
            return false;
        }

        bool extends(const Type& type) const {
            Type* st = (Type*)supertype;
            while (st != nullptr) {
                if (*st == type)
                    return true;
                st = (Type*)st->Supertype;
            }
            return false;
        }
    };

    template<typename T>
    const Type& getType() {
        return T::TYPE;
    }
}