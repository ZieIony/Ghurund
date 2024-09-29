#pragma once

#include "ui/loading/IDrawableFactory.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::UI {
    class DrawableFactory:public Ghurund::UI::IDrawableFactory {
    private:
        ResourceManager& resourceManager;

    public:
        DrawableFactory(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual Drawable* makeDrawable(const ResourcePath& path) override;
    };
}