#pragma once

#include "BaseTypedProperty.h"

namespace Ghurund::Core {
    template<class OwnerT, class PropType>
    class BaseTypedRWProperty:public BaseTypedProperty<OwnerT, PropType> {
    protected:
        typedef std::function<PropType(OwnerT&)> Getter;
        typedef std::function<void(OwnerT&, PropType)> Setter;

    private:
        Getter getter = nullptr;
        Setter setter = nullptr;

    public:
        BaseTypedRWProperty(
            const AString& name,
            Getter getter,
            Setter setter,
            const AString& group = BaseTypedProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name) {
            this->getter = getter;
            this->setter = setter;
        }

        BaseTypedRWProperty(
            const AString& name,
            Getter getter,
            const AString& group = BaseTypedProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name) {
            this->getter = getter;
        }

        BaseTypedRWProperty(
            const AString& name,
            Setter setter,
            const AString& group = BaseTypedProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name) {
            this->setter = setter;
        }

        inline PropType get(OwnerT& owner) const {
            return getter(owner);
        }

        inline void set(OwnerT& owner, PropType value) const {
            setter(owner, value);
        }

        virtual bool canRead() const override {
            return getter != nullptr;
        }

        virtual bool canWrite() const override {
            return setter != nullptr;
        }
    };

    template<class OwnerT, class PropType>
    class Property:public BaseTypedRWProperty<OwnerT, PropType> {
    public:
        Property(
            const AString& name,
            BaseTypedRWProperty<OwnerT, PropType>::Getter getter,
            BaseTypedRWProperty<OwnerT, PropType>::Setter setter,
            const AString& group = BaseTypedRWProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedRWProperty<OwnerT, PropType>(name, getter, setter, group) {}

        Property(
            const AString& name,
            BaseTypedRWProperty<OwnerT, PropType>::Getter getter,
            const AString& group = BaseTypedRWProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedRWProperty<OwnerT, PropType>(name, getter, group) {}

        Property(
            const AString& name,
            BaseTypedRWProperty<OwnerT, PropType>::Setter setter,
            const AString& group = BaseTypedRWProperty<OwnerT, PropType>::DEFAULT_GROUP
        ):BaseTypedRWProperty<OwnerT, PropType>(name, setter, group) {}

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType val = BaseTypedRWProperty<OwnerT, PropType>::get(*(OwnerT*)obj);
            onGet((void*)&val);
        }

        virtual void setRaw(void* obj, void* val) const override {
            BaseTypedRWProperty<OwnerT, PropType>::set(*(OwnerT*)obj, *(std::remove_cvref_t<PropType>*)val);
        }
    };

    template<class OwnerT, class PropType>
    class Property<OwnerT, PropType*>:public BaseTypedRWProperty<OwnerT, PropType*> {
    public:
        Property(
            const AString& name,
            BaseTypedRWProperty<OwnerT, PropType*>::Getter getter,
            BaseTypedRWProperty<OwnerT, PropType*>::Setter setter,
            const AString& group = BaseTypedRWProperty<OwnerT, PropType*>::DEFAULT_GROUP
        ):BaseTypedRWProperty<OwnerT, PropType*>(name, getter, setter, group) {}

        Property(
            const AString& name,
            BaseTypedRWProperty<OwnerT, PropType*>::Getter getter,
            const AString& group = BaseTypedRWProperty<OwnerT, PropType*>::DEFAULT_GROUP
        ):BaseTypedRWProperty<OwnerT, PropType*>(name, getter, group) {}

        Property(
            const AString& name,
            BaseTypedRWProperty<OwnerT, PropType*>::Setter setter,
            const AString& group = BaseTypedRWProperty<OwnerT, PropType*>::DEFAULT_GROUP
        ):BaseTypedRWProperty<OwnerT, PropType*>(name, setter, group) {}

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType* val = BaseTypedRWProperty<OwnerT, PropType*>::get(*(OwnerT*)obj);
            onGet((void*)val);
        }

        virtual void setRaw(void* obj, void* val) const override {
            BaseTypedRWProperty<OwnerT, PropType*>::set(*(OwnerT*)obj, (PropType*)val);
        }
    };
}