#pragma once

#include "BaseProperty.h"

namespace Ghurund::Core {
    template<class OwnerT, class PropType>
    class Property:public BaseProperty {
    protected:
        typedef std::function<PropType(OwnerT&)> Getter;
        typedef std::function<void(OwnerT&, PropType)> Setter;

    protected:
        Getter getter = nullptr;
        Setter setter = nullptr;

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
        Property(
            const AString& name,
            Getter getter,
            Setter setter,
            const AString& group = DEFAULT_GROUP
        ):BaseProperty(
            name,
            group
            ), getter(getter), setter(setter) {}

        Property(
            const AString& name,
            Getter getter,
            const AString& group = DEFAULT_GROUP
        ):Property<OwnerT, PropType>(name, getter, nullptr, group) {}

        Property(
            const AString& name,
            Setter setter,
            const AString& group = DEFAULT_GROUP
        ):Property<OwnerT, PropType>(name, nullptr, setter, group) {}

        inline PropType get(OwnerT& owner) const {
            return getter(owner);
        }

        inline void set(OwnerT& owner, PropType value) const {
            setter(owner, value);
        }

        virtual void getRaw(void* obj, std::function<void(void*)> onGet) const override {
            PropType val = get(*(OwnerT*)obj);
            onGet((void*)&val);
        }

        virtual void setRaw(void* obj, void* val) const override {
            set(*(OwnerT*)obj, *(std::remove_cvref_t<PropType>*)val);
        }
    };
}