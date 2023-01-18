#pragma once

#include "core/reflection/Type.h"
#include "ui/loading/TextFormatFactory.h"

namespace UnitTest {
    class TextFormatFactory: public Ghurund::UI::TextFormatFactory {
    public:
        virtual Ghurund::UI::TextFormat* makeTextFormat() override {
            return nullptr;
        }
    };
}
