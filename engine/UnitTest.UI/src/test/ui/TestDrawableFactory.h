#pragma once

#include "ui/loading/IDrawableFactory.h"

namespace UnitTest {
    class TestDrawableFactory: public Ghurund::UI::IDrawableFactory {
    public:
        virtual Ghurund::UI::Drawable* makeDrawable(const Ghurund::Core::ResourcePath& path) override {
            return nullptr;
        }
    };
}
