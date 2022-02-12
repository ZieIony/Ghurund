#pragma once

#include "BaseTypedProperty.h"
#include "OperationNotSupportedException.h"

namespace Ghurund::Core {
    template<class OwnerT, class PropType>
    class BaseTypedWriteOnlyProperty:public BaseTypedProperty<OwnerT, PropType> {
    protected:
        typedef std::function<void(OwnerT&, PropType)> Setter;

    private:
        Setter setter = nullptr;

    public:
        BaseTypedWriteOnlyProperty(
            const AString& name,
            Setter setter,
            const AString& group = BaseTypedProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, group) {
            this->setter = setter;
        }

        inline void set(OwnerT& owner, PropType value) const {
            setter(owner, value);
        }

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            throw OperationNotSupportedException(std::format(
                "{}::{}::{} is a write-only property.\n",
                BaseTypedProperty<OwnerT, PropType>::getOwnerType().Namespace,
                BaseTypedProperty<OwnerT, PropType>::getOwnerType().Name,
                BaseTypedProperty<OwnerT, PropType>::Type.Name
            ).c_str());
        }

        virtual bool canRead() const override {
            return false;
        }

        virtual bool canWrite() const override {
            return true;
        }
    };

    template<class OwnerT, class PropType>
    class WriteOnlyProperty:public BaseTypedWriteOnlyProperty<OwnerT, PropType> {
    public:
        WriteOnlyProperty(
            const AString& name,
            BaseTypedWriteOnlyProperty<OwnerT, PropType>::Setter setter,
            const AString& group = BaseTypedWriteOnlyProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedWriteOnlyProperty<OwnerT, PropType>(name, setter, group) {}

        virtual void setRaw(void* obj, void* val) const override {
            BaseTypedWriteOnlyProperty<OwnerT, PropType>::set(*(OwnerT*)obj, *(std::remove_cvref_t<PropType>*)val);
        }
    };

    template<class OwnerT, class PropType>
    class WriteOnlyProperty<OwnerT, PropType*>:public BaseTypedWriteOnlyProperty<OwnerT, PropType*> {
    public:
        WriteOnlyProperty(
            const AString& name,
            BaseTypedWriteOnlyProperty<OwnerT, PropType>::Setter setter,
            const AString& group = BaseTypedWriteOnlyProperty<OwnerT, PropType*>::DEFAULT_GROUP
        ):BaseTypedWriteOnlyProperty<OwnerT, PropType*>(name, setter, group) {}

        virtual void setRaw(void* obj, void* val) const override {
            BaseTypedWriteOnlyProperty<OwnerT, PropType*>::set(*(OwnerT*)obj, (PropType*)val);
        }
    };
}