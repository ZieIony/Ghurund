#pragma once

#include "ui/text/TextFormat.h"

namespace Ghurund::UI {
    class TextFormatFactory {
    public:
        virtual ~TextFormatFactory() = 0 {}

        virtual UI::TextFormat* makeTextFormat() = 0;
    };
}