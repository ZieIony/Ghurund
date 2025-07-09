#pragma once

#include "core/NotNull.h"
#include "core/resource/ResourceManager.h"
#include "ui/loading/IDrawableFactory.h"

namespace Ghurund::UI {
    class DrawableFactory:public Ghurund::UI::IDrawableFactory {
    private:
        // borrowed
        ResourceManager* resourceManager;

    public:
        DrawableFactory(NotNull<ResourceManager> resourceManager):resourceManager(&resourceManager) {}

        virtual Drawable* makeDrawable(const ResourcePath& path) override;
    };
}