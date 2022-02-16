#pragma once
#include "core/Exceptions.h"
#include "core/string/String.h"
#include "core/Observable.h"

#include <regex>

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Control;

    class Binding {
    private:
        Control& target;
        BaseProperty* sourceProperty;
        const BaseProperty* targetProperty = nullptr;
        List<AString> path;
        AString propertyName;

        Control* resolvePath(const Array<AString>& path);

    public:
        Binding(Control& target, BaseProperty* targetProperty, BaseProperty* sourceProperty)
            :target(target), targetProperty(targetProperty), sourceProperty(sourceProperty) {}

        void parse(AString& attrName, AString& attrValue);

        void execute();
    };
}