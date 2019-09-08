#pragma once

#include "Constructor.h"
#include "TypeModifier.h"

namespace Ghurund {
	class Type {
	private:
		const BaseConstructor* constructor;
        const TypeModifier modifiers;
		const char* _namespace;
		const char* name;
        const size_t size;
        const Type* supertype;

		static List<Type>& getTypes() {
			static List<Type> types;
			return types;
		}

    public:
        Type(const BaseConstructor* constructor, TypeModifier modifiers, const char* _namespace, const char* name, size_t size, Type* supertype):modifiers(modifiers), size(size) {
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

		bool operator==(const Type& type) const {
			return constructor == type.constructor && strcmp(_namespace, type._namespace) == 0 && strcmp(name, type.name) == 0;
		}

		inline static const List<Type>& TYPES = getTypes();

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