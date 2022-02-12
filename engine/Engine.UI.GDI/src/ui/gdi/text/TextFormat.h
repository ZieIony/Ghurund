#pragma once

#include "ui/gdi/font/Font.h"
#include "ui/text/TextFormat.h"

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class Canvas;
    class Control;

    class TextFormat:public Ghurund::UI::TextFormat {

    protected:
        const Ghurund::Core::Type& GET_TYPE();

    public:
        TextFormat(Ghurund::UI::GDI::Font* font, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :Ghurund::UI::TextFormat(font, size, weight, italic, locale) {
        }

        ~TextFormat();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}