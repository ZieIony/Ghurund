#pragma once

#include <functional>

namespace Ghurund {
    class Property {
    private:
        const char* typeName;
        const char* propertyName;
        std::function<void* (void*)> get;
        std::function<void(void*, void*)> set;

    public:
        Property(const char* typeName, const char* propertyName, std::function<void* (void*)> get, std::function<void(void*, void*)> set):
            typeName(typeName), propertyName(propertyName), get(get), set(set) {}
    };

    template<class OwnerType, class PropType>
    class TypedProperty:public Property {
    public:
        TypedProperty(const char* typeName, const char* propertyName, PropType (OwnerType::*get)() const, void (OwnerType::*set)(PropType)):
            Property(typeName, propertyName, [get](void* owner)->void* {
            OwnerType* o = (OwnerType*)owner;
            PropType p = (o->*get)();
            return (void*)p;
        }, [set](void* owner, void* value) {
            OwnerType* o = (OwnerType*)owner;
            PropType p = (PropType)value;
            (o->*set)(p);
        }) {}
    };
}