#pragma once

#include "PropertyLoader.h"
#include "ui/text/TextDocument.h"

namespace Ghurund::UI {

    class TextDocumentPropertyLoader :public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const TextDocument&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            TextDocument t = convertText<char, wchar_t>(text);
            property.setRaw(&obj, &t);
        }
    };
}