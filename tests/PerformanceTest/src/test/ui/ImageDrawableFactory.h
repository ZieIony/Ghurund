#pragma once

#include "core/reflection/Type.h"
#include "ui/loading/ImageDrawableFactory.h"

namespace UnitTest {
    class DrawableFactory: public Ghurund::UI::DrawableFactory {
    public:
        virtual Ghurund::UI::ImageDrawable* makeDrawable(const Ghurund::Core::FilePath& path) override {
            return nullptr;
        }
    };
}
