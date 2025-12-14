#pragma once

#include "PropertyLoader.h"
#include "ui/text/TextDocument.h"

namespace Ghurund::UI {

    class TextDocumentPropertyLoader:public PropertyLoader {
    private:
        Font* defaultFont;
        Color defaultColor;

    public:
        TextDocumentPropertyLoader(NotNull<Font> defaultFont, Color defaultColor):defaultFont(&defaultFont), defaultColor(defaultColor) {
            defaultFont->addReference();
        }

        virtual const Type& getType() const override {
            return Ghurund::Core::getType<const TextDocument&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const AString& text) const override {
            TextDocument t = TextDocument(convertText<char, wchar_t>(text), defaultFont, defaultColor);
            property.setRaw(&obj, &t);
        }
    };
}