#include "ghuipch.h"
#include "Binding.h"

#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
    Control* Binding::resolvePath(const Array<AString>& path) {
        Control* result = &target;
        for (const AString& part : path) {
            if (part == "Parent") {
                result = result->Parent;
            } else {
                result = result->find(part);
            }
            if (!result) {
                if (part == "parent") {
                    Logger::log(LogType::WARNING, _T("Could not find control 'parent', did you mean 'Parent'?\n"));
                } else {
                    Logger::log(LogType::WARNING, std::format(_T("Could not find control '{}'.\n"), part).c_str());
                }
                return nullptr;
            }
        }
        return result;
    }

    void Binding::parse(AString& attrName, AString& attrValue) {
        std::regex regex(" *\\{ *((?:(?:parent|[a-zA-Z0-9_]+)\\/)*)([a-zA-Z0-9_]+) *\\} *");
        std::smatch m;
        std::string s = attrValue.Data;
        if (std::regex_match(s, m, regex)) {
            path.clear();
            path.addAll(AString(m[1].str().c_str()).split("/"));
            propertyName = m[2].str().c_str();
        } else {
            throw InvalidParamException(std::format("Invalid binding string: '{}'", attrValue).c_str());
        }

        size_t propIndex = target.Type.Properties.find([&](const BaseProperty& prop) {
            return prop.Name == attrName;
        });
        if (propIndex != target.Type.Properties.Size) {
            targetProperty = &target.Type.Properties[propIndex].get();
        } else {
            auto message = std::format("Object '{}::{}' of type '{}' doesn't have the specified property: '{}'",
                target.Type.Namespace, target.Type.Name, attrName, attrValue);
            throw InvalidDataException(message.c_str());
        }
    }
    
    void Binding::execute() {
        Control* result = resolvePath(path);
        if (result) {
            size_t sourcePropIndex = result->Type.Properties.find([&](const BaseProperty& prop) {
                return prop.Name == propertyName;
            });
            if (sourcePropIndex != result->Type.Properties.Size) {
                const BaseProperty* sourceProperty = &result->Type.Properties[sourcePropIndex].get();
                if (sourceProperty->Type == targetProperty->Type) { // TODO: extends
                    sourceProperty->getRaw(result, [&](void* val) {
                        targetProperty->setRaw(this, val);
                    });
                } else {
                    Logger::log(LogType::WARNING, std::format(_T("Invalid binding property type: '{}'.\n"), propertyName).c_str());
                }
            } else {
                Logger::log(LogType::WARNING, std::format(_T("Invalid binding source: '{}'.\n"), propertyName).c_str());
            }
        } else {
            //Logger::log(LogType::WARNING, std::format(_T("Invalid binding path: '{}'.\n"), path).c_str());
        }
    }
}