#pragma once

#include "BaseProperty.h"
#include "Type.h"

namespace Ghurund::Core {
    template<class OwnerT, class PropType>
    class BaseTypedProperty:public BaseProperty {
    public:
        BaseTypedProperty(
            const AString& name,
            const AString& group = DEFAULT_GROUP
        ):BaseProperty(
            Ghurund::Core::getType<std::remove_cvref<std::remove_pointer<PropType>::type>::type>(),
            std::is_pointer_v<PropType>,
            name,
            group
        ) {}

        virtual const Ghurund::Core::Type& getOwnerType() const override {
            return Ghurund::Core::getType<OwnerT>();
        }
    };
}