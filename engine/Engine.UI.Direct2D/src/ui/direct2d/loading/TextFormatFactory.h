#pragma once

#include "ui/loading/TextFormatFactory.h"

namespace Ghurund::UI::Direct2D {
    class TextFormatFactory:public Ghurund::UI::TextFormatFactory {
    public:
        virtual TextFormat* makeTextFormat() override {
            throw NotImplementedException();
        }
    };
}