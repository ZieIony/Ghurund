#pragma once

#include "core/object/NotNull.h"
#include "core/resource/ResourceManager.h"
#include "ui/loading/IDrawableFactory.h"

namespace Ghurund::UI {
    class DrawableFactory:public Ghurund::UI::IDrawableFactory {
    private:
        ResourceManager& resourceManager;

    public:
        DrawableFactory(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual Drawable* makeDrawable(const ResourcePath& path) override;
    };
}