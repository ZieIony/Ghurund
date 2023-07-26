#pragma once

#include "ui/loading/DrawableFactory.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::UI::Direct2D {
    class DrawableFactory:public Ghurund::UI::DrawableFactory {
    private:
        ResourceManager& resourceManager;

    public:
        DrawableFactory(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual Drawable* makeDrawable(const FilePath& path) override;
    };
}