#pragma once

#include "PropertyLoader.h"
#include "core/math/Int.h"
#include "core/math/Float.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::UI {
    class BoolPropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<bool>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            bool b;
            if (text == "true") {
                b = true;
            } else if (text == "false") {
                b = false;
            } else {
                throw InvalidDataException(std::format("'{}' is not a valid bool value.", text).c_str());
            }
            property.setRaw(&obj, &b);
        }
    };

    class UInt32PropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<uint32_t>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            uint32_t i = parse<uint32_t>(text);
            property.setRaw(&obj, &i);
        }
    };

    class FloatPropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<float>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            float f = parse<float>(text);
            property.setRaw(&obj, &f);
        }
    };
}