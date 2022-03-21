#pragma once

#include "ui/loading/ImageDrawableFactory.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::UI::Direct2D {
    class ImageDrawableFactory:public Ghurund::UI::ImageDrawableFactory {
    private:
        ResourceManager& resourceManager;

    public:
        ImageDrawableFactory(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual ImageDrawable* makeDrawable(const FilePath& path) override;
    };
}