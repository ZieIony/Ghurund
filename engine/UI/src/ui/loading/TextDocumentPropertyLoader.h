#pragma once

#include "PropertyLoader.h"
#include "ui/text/TextDocument.h"

namespace Ghurund::UI {

    class TextDocumentPropertyLoader:public PropertyLoader {
    private:
        TextStyle* defaultTextStyle;
        Color defaultColor;

    public:
        TextDocumentPropertyLoader(
            NotNull<TextStyle> defaultTextStyle,
            Color defaultColor
        ):defaultTextStyle(&defaultTextStyle), defaultColor(defaultColor) {
            defaultTextStyle->addReference();
        }

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const TextDocument&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            TextDocument t = TextDocument(convertText<char, wchar_t>(text), defaultTextStyle, defaultColor);
            property.setRaw(&obj, &t);
        }
    };
}