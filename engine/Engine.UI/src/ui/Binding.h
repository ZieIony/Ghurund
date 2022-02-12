#pragma once
#include "core/Exceptions.h"
#include "core/string/String.h"

#include <regex>

namespace Ghurund::UI {
    class BindingPath {
    private:
        Array<AString> sourcePath;
        AString propertyName;

    public:
        BindingPath(const Array<AString>& sourcePath, const AString& propertyName):sourcePath(sourcePath), propertyName(propertyName) {}

        inline const Array<AString>& getSourcePath() const {
            return sourcePath;
        }

        __declspec(property(get = getPath)) const Array<AString>& SourcePath;

        inline const AString& getPropertyName() const {
            return propertyName;
        }

        __declspec(property(get = getPropertyName)) const AString& PropertyName;

        static BindingPath parse(const AString& binding) {
            std::regex regex(" *\\{ *((?:(?:parent|[a-zA-Z0-9_]+)\\/)*)([a-zA-Z0-9_]+) *\\} *");
            std::smatch m;
            std::string s = binding.Data;
            if (std::regex_match(s, m, regex)) {
                Array<AString> path = AString(m[1].str().c_str()).split("/");
                AString propertyName = m[2].str().c_str();
                return BindingPath(path, propertyName);
            } else {
                throw InvalidParamException("invalid binding string");
            }
        }
    };

    class Control;

    class Binding {
    private:
        Control* target;
        BaseProperty* sourceProperty;
        BaseProperty* targetProperty;
        Array<AString> path;

    public:
        Binding(Control* target, BaseProperty* targetProperty, BaseProperty* sourceProperty, Array<AString> path)
            :target(target), targetProperty(targetProperty), sourceProperty(sourceProperty), path(path) {}

        void execute() {
            //            target.resolvePath(
        }
    };
}