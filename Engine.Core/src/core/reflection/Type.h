#pragma once

#include "Constructor.h"
#include "Property.h"
#include "TypeModifier.h"
#include "core/collection/List.h"
#include "core/collection/Map.h"
#include "core/string/AString.h"

namespace Ghurund {
	class Type {
	private:
		const BaseConstructor* constructor;
        const TypeModifier modifiers;
		const char* _namespace;
		const char* name;
        const size_t size;
        const Type* supertype;
        const Map<AString, Property*> properties;

		static List<Type>& getTypes() {
			static List<Type> types;
			return types;
		}

    public:
        Type(const BaseConstructor* constructor, TypeModifier modifiers, const char* _namespace, const char* name, size_t size, Type* supertype, Map<AString, Property*>& properties):
            modifiers(modifiers), size(size), properties(properties) {
            this->constructor = constructor;
            this->_namespace = _namespace;
            this->name = name;
            this->supertype = supertype;

            getTypes().add(*this);
        }

        static Type* fromName(const char* _namespace, const char* name) {
            for (Type& type : TYPES) {
                if (strcmp(type.Namespace, _namespace) == 0 && strcmp(type.Name, name) == 0)
                    return &type;
            }
            return nullptr;
        }

		const BaseConstructor* getConstructor() const {
			return constructor;
		}

		__declspec(property(get = getConstructor)) BaseConstructor* Constructor;

		const char* getNamespace() const {
			return _namespace;
		}

		__declspec(property(get = getNamespace)) const char* Namespace;

        const char* getName() const {
            return name;
        }

        __declspec(property(get = getName)) const char* Name;

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

        const Map<AString, Property*>& getProperties() const {
            return properties;
        }

        __declspec(property(get = getProperties)) const Map<AString, Property*>& Properties;

		bool operator==(const Type& type) const {
			return constructor == type.constructor && strcmp(_namespace, type._namespace) == 0 && strcmp(name, type.name) == 0;
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
}