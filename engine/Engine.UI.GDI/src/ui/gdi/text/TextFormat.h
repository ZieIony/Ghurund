#pragma once

#include "ui/gdi/font/Font.h"
#include "ui/text/TextFormat.h"

struct IDWriteTextFormat;

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class Canvas;
    class Control;

    class TextFormat:public Ghurund::UI::TextFormat {
    private:
        IDWriteTextFormat* format = nullptr;

    protected:
        const Ghurund::Core::Type& GET_TYPE();

    public:
        TextFormat(Ghurund::UI::GDI::Font* font, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :Ghurund::UI::TextFormat(font, size, weight, italic, locale) {
        }

        TextFormat(IDWriteTextFormat* format, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :Ghurund::UI::TextFormat(nullptr, size, weight, italic, locale) {
            this->format = format;
            format->AddRef();
        }

        ~TextFormat();

        Status init(IDWriteFactory5& dwriteFactory);

        inline IDWriteTextFormat* getFormat() {
            return format;
        }

        __declspec(property(get = getFormat)) IDWriteTextFormat* Format;

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}