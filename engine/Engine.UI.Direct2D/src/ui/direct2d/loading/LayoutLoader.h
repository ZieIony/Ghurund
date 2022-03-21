#pragma once

#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI::Direct2D {
    class LayoutLoader:public Ghurund::UI::LayoutLoader{
    public:
        LayoutLoader(
            Ghurund::Core::ResourceManager& resourceManager,
            ShapeFactory& shapeFactory,
            ImageDrawableFactory& imageDrawableFactory,
            TextFormatFactory& textFormatFactory
        ):Ghurund::UI::LayoutLoader(
            resourceManager,
            shapeFactory,
            imageDrawableFactory,
            textFormatFactory
        ) {

        }
    };
}