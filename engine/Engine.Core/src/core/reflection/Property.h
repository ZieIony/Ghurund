#pragma once

#include "BaseProperty.h"
#include "Type.h"

#include <functional>

namespace Ghurund::Core {
    template<class OwnerType, class PropType>
    class ReadOnlyProperty:public BaseProperty {
    protected:
        typedef std::function<PropType(OwnerType&)> Getter;

    private:
        Getter getter = nullptr;

    public:
        ReadOnlyProperty(
            const AString& name,
            Getter getter
        ):BaseProperty(Ghurund::Core::getType<std::remove_cvref<std::remove_pointer<PropType>::type>::type>(), name) {
            this->getter = getter;
        }

        inline PropType get(OwnerType& owner) {
            return getter(owner);
        }
    };

    template<class OwnerType, class PropType>
    class WriteOnlyProperty:public BaseProperty {
    protected:
        typedef std::function<void(OwnerType&, PropType)> Setter;

    private:
        Setter setter = nullptr;

    public:
        WriteOnlyProperty(
            const AString& name,
            Setter setter
        ):BaseProperty(Ghurund::Core::getType<PropType>(), name) {
            auto TYPE = Ghurund::Core::getType<std::remove_cvref<std::remove_pointer<PropType>::type>::type>();
            this->setter = setter;
        }

        inline void set(OwnerType& owner, PropType value) {
            setter(owner, value);
        }
    };

    template<class OwnerType, class PropType>
    class Property:public BaseProperty {
    protected:
        typedef std::function<PropType(OwnerType&)> Getter;
        typedef std::function<void(OwnerType&, PropType)> Setter;

    private:
        Getter getter = nullptr;
        Setter setter = nullptr;

    public:
        Property(
            const AString& name,
            Getter getter,
            Setter setter
        ):BaseProperty(Ghurund::Core::getType<std::remove_cvref<std::remove_pointer<PropType>::type>::type>(), name) {
            this->getter = getter;
            this->setter = setter;
        }

        inline PropType get(OwnerType& owner) {
            return getter(owner);
        }

        inline void set(OwnerType& owner, PropType value) {
            setter(owner, value);
        }
    };
}