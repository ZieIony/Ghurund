#pragma once

#include "core/string/String.h"

#include <functional>

namespace Ghurund::Core {
    class Type;

    class BaseProperty {
    private:
        const AString name;
        const AString group;

        BaseProperty(const BaseProperty& other) = delete;
        BaseProperty(BaseProperty&& other) = delete;

    protected:
        virtual const Type& getOwnerTypeImpl() const = 0;
        virtual const Type& getTypeImpl() const = 0;
        virtual bool canReadImpl() const = 0;
        virtual bool canWriteImpl() const = 0;

    public:
        static const inline char* DEFAULT_GROUP = "default";

        BaseProperty(
            const AString& name,
            const AString& group = DEFAULT_GROUP
        ):name(name), group(group) {}

        virtual ~BaseProperty() = 0 {}

        inline const Type& getOwnerType() const {
            return getOwnerTypeImpl();
        }

        __declspec(property(get = getOwnerType)) const Type& OwnerType;

        inline const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

        inline const Ghurund::Core::Type& getType() const {
            return getTypeImpl();
        }

        __declspec(property(get = getType)) const Type& Type;

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const = 0;
        virtual void setRaw(void* obj, void* val) const = 0;

        inline bool canRead() const {
            return canReadImpl();
        }

        __declspec(property(get = canRead)) bool CanRead;

        inline bool canWrite() const {
            return canWriteImpl();
        }

        __declspec(property(get = canWrite)) bool CanWrite;
    };
}