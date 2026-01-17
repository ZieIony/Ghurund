#pragma once

#include "core/collection/Array.h"
#include "core/collection/List.h"
#include "core/reflection/BaseProperty.h"
#include "core/string/String.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Control;

    class Binding2 {
    private:
        Control& target;
        BaseProperty* sourceProperty;
        const BaseProperty* targetProperty = nullptr;
        List<AString> path;
        AString propertyName;

        Control* resolvePath(const Array<AString>& path);

    public:
        Binding2(Control& target, BaseProperty* targetProperty, BaseProperty* sourceProperty)
            :target(target), targetProperty(targetProperty), sourceProperty(sourceProperty) {}

        void parse(AString& attrName, AString& attrValue);

        void execute();
    };
}