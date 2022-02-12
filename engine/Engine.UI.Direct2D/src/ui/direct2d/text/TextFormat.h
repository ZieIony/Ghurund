#pragma once

#include "ui/direct2d/font/Font.h"
#include "ui/text/TextFormat.h"

struct IDWriteTextFormat;

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class TextFormat:public Ghurund::UI::TextFormat {
    private:
        IDWriteTextFormat* format = nullptr;

    protected:
        const Ghurund::Core::Type& GET_TYPE();

    public:
        TextFormat(Ghurund::UI::Direct2D::Font* font, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
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

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}