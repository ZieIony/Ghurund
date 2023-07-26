#pragma once

#include "core/reflection/Type.h"
#include "ui/loading/DrawableFactory.h"

namespace UnitTest {
    class DrawableFactory: public Ghurund::UI::DrawableFactory {
    public:
        virtual Ghurund::UI::Drawable* makeDrawable(const Ghurund::Core::FilePath& path) override {
            return nullptr;
        }
    };
}
