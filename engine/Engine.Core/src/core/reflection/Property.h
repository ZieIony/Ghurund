#pragma once

#include "BaseProperty.h"

namespace Ghurund::Core {
    template<class OwnerT, class PropType>
    class BaseTypedProperty:public BaseProperty {
    protected:
        typedef std::function<PropType(OwnerT&)> Getter;
        typedef std::function<void(OwnerT&, PropType)> Setter;

    private:
        Getter getter = nullptr;
        Setter setter = nullptr;

    protected:
        virtual const Ghurund::Core::Type& getOwnerTypeImpl() const override {
            return Ghurund::Core::getType<OwnerT>();
        }

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return Ghurund::Core::getType<PropType>();
        }

        virtual bool canReadImpl() const override {
            return getter != nullptr;
        }

        virtual bool canWriteImpl() const override {
            return setter != nullptr;
        }

    public:
        BaseTypedProperty(
            const AString& name,
            Getter getter,
            Setter setter,
            const AString& group = DEFAULT_GROUP
        ):BaseProperty(
            name,
            group
            ), getter(getter), setter(setter) {}

        BaseTypedProperty(
            const AString& name,
            Getter getter,
            const AString& group = DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, getter, nullptr, group) {}

        BaseTypedProperty(
            const AString& name,
            Setter setter,
            const AString& group = DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, nullptr, setter, group) {}

        inline PropType get(OwnerT& owner) const {
            return getter(owner);
        }

        inline void set(OwnerT& owner, PropType value) const {
            setter(owner, value);
        }
    };

    template<class OwnerT, class PropType>
    class Property:public BaseTypedProperty<OwnerT, PropType> {
    public:
        Property(
            const AString& name,
            BaseTypedProperty<OwnerT, PropType>::Getter getter,
            BaseTypedProperty<OwnerT, PropType>::Setter setter,
            const AString& group = BaseProperty::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, getter, setter, group) {}

        Property(
            const AString& name,
            BaseTypedProperty<OwnerT, PropType>::Getter getter,
            const AString& group = BaseProperty::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, getter, group) {}

        Property(
            const AString& name,
            BaseTypedProperty<OwnerT, PropType>::Setter setter,
            const AString& group = BaseProperty::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType>(name, setter, group) {}

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType val = BaseTypedProperty<OwnerT, PropType>::get(*(OwnerT*)obj);
            onGet((void*)&val);
        }

        virtual void setRaw(void* obj, void* val) const override {
            BaseTypedProperty<OwnerT, PropType>::set(*(OwnerT*)obj, *(std::remove_cvref_t<PropType>*)val);
        }
    };

    template<class OwnerT, class PropType>
    class Property<OwnerT, PropType*>:public BaseTypedProperty<OwnerT, PropType*> {
    public:
        Property(
            const AString& name,
            BaseTypedProperty<OwnerT, PropType*>::Getter getter,
            BaseTypedProperty<OwnerT, PropType*>::Setter setter,
            const AString& group = BaseProperty::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType*>(name, getter, setter, group) {}

        Property(
            const AString& name,
            BaseTypedProperty<OwnerT, PropType*>::Getter getter,
            const AString& group = BaseProperty::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType*>(name, getter, group) {}

        Property(
            const AString& name,
            BaseTypedProperty<OwnerT, PropType*>::Setter setter,
            const AString& group = BaseProperty::DEFAULT_GROUP
        ):BaseTypedProperty<OwnerT, PropType*>(name, setter, group) {}

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType* val = BaseTypedProperty<OwnerT, PropType*>::get(*(OwnerT*)obj);
            onGet((void*)val);
        }

        virtual void setRaw(void* obj, void* val) const override {
            BaseTypedProperty<OwnerT, PropType*>::set(*(OwnerT*)obj, (PropType*)val);
        }
    };
}