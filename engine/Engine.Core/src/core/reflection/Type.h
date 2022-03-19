#pragma once

#include "Constructor.h"
#include "BaseProperty.h"
#include "Method.h"
#include "TypeModifier.h"
#include "core/collection/List.h"
#include "core/string/String.h"
#include "core/Object.h"
#include "core/Concepts.h"
#include "core/Exceptions.h"
#include "BaseType.h"
#include "ConstructorCollection.h"

namespace Ghurund::Core {
    class Type:public NamedObject<char> {
    private:
        const TypeModifier modifiers;
        const Type* baseType;
        const AString _namespace;
        const size_t size;
        const Type* supertype;
        const ConstructorCollection constructors;
        const Array<std::reference_wrapper<const BaseProperty>> properties;
        const Array<std::reference_wrapper<const BaseMethod>> methods;
        const Array<std::reference_wrapper<const Type>> templateParams;
        const bool _const, pointer, ref, _volatile;

        static List<std::reference_wrapper<const Type>>& getTypes() {
            static List<std::reference_wrapper<const Type>> types;
            return types;
        }

        Type(const Type& other) = delete;
        Type(Type&& other) = delete;

    public:
        Type(const char* name, size_t size):
            NamedObject<char>(name),
            baseType(this),
            modifiers((TypeModifier)0),
            size(size),
            _const(false),
            pointer(false),
            ref(false),
            _volatile(false) {
            getTypes().add(*this);
        }

        Type(const char* _namespace, const char* name, size_t size):
            NamedObject<char>(name),
            _namespace(_namespace),
            baseType(this),
            modifiers((TypeModifier)0),
            size(size),
            _const(false),
            pointer(false),
            ref(false),
            _volatile(false) {
            getTypes().add(*this);
        }

        Type(
            const Type& baseType,
            bool _const,
            bool pointer,
            bool ref,
            bool _volatile
        ):
            NamedObject<char>(baseType.Name),
            constructors(baseType.Constructors),
            modifiers(baseType.Modifiers),
            baseType(&baseType),
            _namespace(baseType.Namespace),
            size(baseType.Size),
            _const(_const),
            pointer(pointer),
            ref(ref),
            _volatile(_volatile),
            supertype(supertype),
            properties(properties),
            methods(methods),
            templateParams(templateParams) {
            getTypes().add(*this);
        }

        Type(
            const AString& _namespace,
            const AString& name,
            size_t size,
            TypeModifier modifiers,
            const Type* supertype,
            const ConstructorCollection& constructors,
            const Array<std::reference_wrapper<const BaseProperty>>& properties,
            const Array<std::reference_wrapper<const BaseMethod>>& methods,
            const Array<std::reference_wrapper<const Type>> templateParams
        ):
            NamedObject<char>(name),
            constructors(constructors),
            modifiers(modifiers),
            baseType(this),
            _namespace(_namespace),
            size(size),
            _const(false),
            pointer(false),
            ref(false),
            _volatile(false),
            supertype(supertype),
            properties(properties),
            methods(methods),
            templateParams(templateParams) {
            getTypes().add(*this);
        }

        static const Type& byName(const AString& _namespace, const AString& name) {
            for (const Type& type : TYPES) {
                if (type.Namespace == _namespace && type.Name == name)
                    return type;
            }
            throw InvalidParamException(std::format("Type {}::{} could not be located.\n", _namespace.Data, name.Data).c_str());
        }

        const ConstructorCollection& getConstructors() const {
            return constructors;
        }

        __declspec(property(get = getConstructors)) const ConstructorCollection& Constructors;

        inline const Type& getBaseType() const {
            return *baseType;
        }

        __declspec(property(get = getBaseType)) const Type& BaseType;

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

        const Array<std::reference_wrapper<const BaseProperty>>& getProperties() const {
            return properties;
        }

        __declspec(property(get = getProperties)) const Array<std::reference_wrapper<const BaseProperty>>& Properties;

        const Array<std::reference_wrapper<const BaseMethod>>& getMethods() const {
            return methods;
        }

        __declspec(property(get = getMethods)) const Array<std::reference_wrapper<const BaseMethod>>& Methods;

        const Array<std::reference_wrapper<const Type>>& getTemplateParams() const {
            return templateParams;
        }

        __declspec(property(get = getTemplateParams)) const Array<std::reference_wrapper<const Type>>& TemplateParams;

        inline bool isTemplate() const {
            return !templateParams.Empty;
        }

        __declspec(property(get = isTemplate)) bool IsTemplate;

        inline bool isPointer() const {
            return pointer;
        }

        __declspec(property(get = isPointer)) bool IsPointer;

        inline bool isReference() const {
            return ref;
        }

        __declspec(property(get = isReference)) bool IsReference;

        inline bool isConst() const {
            return _const;
        }

        __declspec(property(get = isConst)) bool IsConst;

        inline bool isVolatile() const {
            return _volatile;
        }

        __declspec(property(get = isVolatile)) bool IsVolatile;

        bool operator==(const Type& other) const {
            return _namespace == other._namespace && __super::operator==(other) && pointer == other.pointer && ref == other.ref && _const == other._const;
        }

        inline static const List<std::reference_wrapper<const Type>>& TYPES = getTypes();

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
    const Type& getType() = delete;

    template <typename T>
    concept HasType = requires(T obj) {
        { T::GET_TYPE() } -> std::same_as<const Type&>;
    };

    template<HasType T>
    const Type& getType() {
        return T::GET_TYPE();
    }

    template<Qualified T>
    const Type& getType() {
        const Type& baseType = getType<typename BaseType<T>::type>();
        static Type type = Type(baseType, std::is_const_v<T>, std::is_pointer_v<T>, std::is_reference_v<T>, std::is_volatile_v<T>);
        return type;
    }

    template<typename T>
    const Type& getType(const T& obj) {
        return getType<T>();
    }

    template <typename T>
    concept Typed = requires(T obj) {
        { getType(obj) } -> std::same_as<Type>;
    };

    template<>
    String toString(const Type& type);

    template<Typed T>
    String toString(const T& obj) {
        const Type& type = getType<T>();
        return String(std::format(_T("{}::{}"), type.Namespace, _T("::"), type.Name).c_str());
    }

}