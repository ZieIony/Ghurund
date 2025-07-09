#pragma once

#include "core/exception/Exceptions.h"
#include "ui/loading/TextFormatFactory.h"

namespace Ghurund::UI::OpenGL {
    class TextFormatFactory:public Ghurund::UI::TextFormatFactory {
    public:
        virtual TextFormat* makeTextFormat() override {
            throw NotImplementedException();
        }
    };
}