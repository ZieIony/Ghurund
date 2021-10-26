#pragma once

#include "core/Exceptions.h"
#include "ui/loading/TextFormatFactory.h"

namespace Ghurund::UI::GDI {
    class TextFormatFactory:public Ghurund::UI::TextFormatFactory {
    public:
        virtual TextFormat* makeTextFormat() override {
            throw NotImplementedException();
        }
    };
}