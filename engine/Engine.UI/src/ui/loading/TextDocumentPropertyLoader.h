#pragma once

#include "PropertyLoader.h"
#include "ui/text/TextDocument.h"

namespace Ghurund::UI {

    class TextDocumentPropertyLoader :public PropertyLoader {
    public:
        virtual const Type& getType() const override {
            return Ghurund::Core::getType<std::unique_ptr<TextDocument>&>();
        }

        virtual void loadAttr(Object& obj, const BaseProperty& property, const AString& text) const override {
            std::unique_ptr<TextDocument> t = std::make_unique<TextDocument>(convertText<char, wchar_t>(text));
            property.setRaw(&obj, &t);
        }
    };
}