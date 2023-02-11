#pragma once

#include "core/reflection/Type.h"
#include "ui/loading/ImageDrawableFactory.h"

namespace UnitTest {
    class ImageDrawableFactory: public Ghurund::UI::ImageDrawableFactory {
    public:
        virtual Ghurund::UI::ImageDrawable* makeDrawable(const Ghurund::Core::FilePath& path) override {
            return nullptr;
        }
    };
}
