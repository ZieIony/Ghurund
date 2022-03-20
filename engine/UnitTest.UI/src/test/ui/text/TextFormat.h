#pragma once

#include "test/ui/font/Font.h"
#include "ui/text/TextFormat.h"

namespace UnitTest {
    class TextFormat:public Ghurund::UI::TextFormat {
    public:
        TextFormat(UnitTest::Font* font, float size, unsigned int weight = 400, bool italic = false, const Ghurund::Core::WString& locale = L"en-us")
            :Ghurund::UI::TextFormat(font, size, weight, italic, locale) {
        }
    };
}