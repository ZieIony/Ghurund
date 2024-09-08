#pragma once

#include "PropertyLoader.h"

namespace Ghurund::UI {

    class AStringPropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const AString&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            AString t = text;
            property.setRaw(&obj, &t);
        }
    };

    class NullableAStringPropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const AString*>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            const AString* t = &text;
            property.setRaw(&obj, &t);
        }
    };

    class WStringPropertyLoader:public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const WString&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            WString t = convertText<char, wchar_t>(text);
            property.setRaw(&obj, &t);
        }
    };
}