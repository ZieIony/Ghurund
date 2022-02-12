#pragma once

#include "core/string/String.h"

#include <functional>

namespace Ghurund::Core {
    class Type;

    class BaseProperty {
    private:
        const AString name;
        const Type& type;
        const bool pointerType;
        const AString group;

    public:
        static const inline char* DEFAULT_GROUP = "default";

        BaseProperty(
            const Type& type,
            const bool pointerType,
            const AString& name,
            const AString& group = DEFAULT_GROUP
        ):name(name), type(type), pointerType(pointerType), group(group) {}

        virtual ~BaseProperty() = 0 {}

        virtual const Type& getOwnerType() const = 0;

        __declspec(property(get = getOwnerType)) const Type& OwnerType;

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        inline const Type& getType() const {
            return type;
        }

        __declspec(property(get = getType)) const Type& Type;

        inline bool isPointerType() const {
            return pointerType;
        }

        __declspec(property(get = isPointerType)) bool PointerType;

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const = 0;
        virtual void setRaw(void* obj, void* val) const = 0;
        virtual bool canRead() const = 0;
        virtual bool canWrite() const = 0;
    };
}