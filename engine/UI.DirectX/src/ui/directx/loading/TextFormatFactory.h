#pragma once

#include "ui/loading/TextFormatFactory.h"

namespace Ghurund::UI::DirectX {
    class TextFormatFactory:public Ghurund::UI::TextFormatFactory {
    public:
        virtual TextFormat* makeTextFormat() override {
            throw NotImplementedException();
        }
    };
}