#pragma once

#include "BaseTypedProperty.h"
#include "OperationNotSupportedException.h"
#include "core/logging/Formatter.h"

namespace Ghurund::Core {
    template<class OwnerT, class PropType>
    class BaseTypedReadOnlyProperty:public BaseTypedProperty<OwnerT, PropType> {
    protected:
        typedef std::function<PropType(OwnerT&)> Getter;

    private:
        Getter getter = nullptr;

    public:
        BaseTypedReadOnlyProperty(
            const AString& name,
            Getter getter,
            const AString& group = BaseTypedProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, group) {
            this->getter = getter;
        }

        inline PropType get(OwnerT& owner) const {
            return getter(owner);
        }

        virtual void setRaw(void* obj, void* val) const override {
            throw OperationNotSupportedException(std::format(
                "{}::{}::{} is a read-only property.\n",
                BaseTypedProperty<OwnerT, PropType>::getOwnerType().Namespace,
                BaseTypedProperty<OwnerT, PropType>::getOwnerType().Name,
                BaseTypedProperty<OwnerT, PropType>::Type.Name
            ).c_str());
        }

        virtual bool canRead() const override {
            return true;
        }

        virtual bool canWrite() const override {
            return false;
        }
    };

    template<class OwnerT, class PropType>
    class ReadOnlyProperty:public BaseTypedReadOnlyProperty<OwnerT, PropType> {
    public:
        ReadOnlyProperty(
            const AString& name,
            BaseTypedReadOnlyProperty<OwnerT, PropType>::Getter getter,
            const AString& group = BaseTypedReadOnlyProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedReadOnlyProperty<OwnerT, PropType>(name, getter, group) {}

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType val = BaseTypedReadOnlyProperty<OwnerT, PropType>::get(*(OwnerT*)obj);
            onGet((void*)&val);
        }
    };

    template<class OwnerT, class PropType>
    class ReadOnlyProperty<OwnerT, PropType*>:public BaseTypedReadOnlyProperty<OwnerT, PropType*> {
    public:
        ReadOnlyProperty(
            const AString& name,
            BaseTypedReadOnlyProperty<OwnerT, PropType*>::Getter getter,
            const AString& group = BaseTypedReadOnlyProperty<OwnerT, PropType*>::DEFAULT_GROUP
        ):BaseTypedReadOnlyProperty<OwnerT, PropType*>(name, getter, group) {}

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType* val = BaseTypedReadOnlyProperty<OwnerT, PropType*>::get(*(OwnerT*)obj);
            onGet((void*)val);
        }
    };
}