#pragma once

#include "application/Feature.h"
#include "ui/font/FontLoader.h"
#include "ui/image/BitmapLoader.h"
#include "ui/image/ImageLoader.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "graphics/Graphics2D.h"

#include "reflection_be712ce6_5dab_46fc_b10c_6b6f3ac08653.h"

namespace Ghurund {
    using namespace Ghurund::UI;

    class UIFeature:public Feature {
        reflection_be712ce6_5dab_46fc_b10c_6b6f3ac08653

    private:
        Application& app;
        Ghurund::Graphics2D* graphics2d = nullptr;
        Theme* theme = nullptr;
        LayoutLoader* layoutLoader = nullptr;

    public:
        UIFeature(Application& app):app(app) {}

        virtual Status init() override {
            graphics2d = ghnew Ghurund::Graphics2D();
            Status result = graphics2d->init(app.Graphics);
            if (result != Status::OK)
                return result;

            auto fontLoader = ghnew FontLoader(*graphics2d->DWriteFactory);
            result = fontLoader->init();
            if (result != Status::OK)
                return result;
            app.ResourceManager.Loaders.add(Font::TYPE, std::unique_ptr<FontLoader>(fontLoader));
            auto imageLoader = ghnew ImageLoader();
            result = imageLoader->init();
            if (result != Status::OK)
                return result;
            app.ResourceManager.Loaders.add(Image::TYPE, std::unique_ptr<ImageLoader>(imageLoader));
            auto bitmapLoader = ghnew BitmapLoader(*imageLoader, *graphics2d->DeviceContext);
            app.ResourceManager.Loaders.add(Bitmap::TYPE, std::unique_ptr<BitmapLoader>(bitmapLoader));
            auto layoutLoader = ghnew LayoutLoader(*graphics2d->Factory, app.ResourceManager);
            app.ResourceManager.Loaders.add(Layout::TYPE, std::unique_ptr<LayoutLoader>(layoutLoader));
            this->layoutLoader = (LayoutLoader*)app.ResourceManager.Loaders.get(Layout::TYPE);

            return Status::OK;
        }

        virtual void uninit() override {
            app.ResourceManager.Loaders.remove(Layout::TYPE);
            app.ResourceManager.Loaders.remove(Bitmap::TYPE);
            app.ResourceManager.Loaders.remove(Image::TYPE);
            app.ResourceManager.Loaders.remove(Font::TYPE);
            delete graphics2d;
            graphics2d = nullptr;
        }

        inline Ghurund::Graphics2D& getGraphics2D() {
            return *graphics2d;
        }

        __declspec(property(get = getGraphics2D)) Ghurund::Graphics2D& Graphics2D;

        inline Theme* getTheme() {
            return layoutLoader ? layoutLoader->Theme : nullptr;
        }

        inline void setTheme(Theme* theme) {
            if (layoutLoader)
                layoutLoader->Theme = theme;
        }

        __declspec(property(get = getTheme, put = setTheme)) Ghurund::UI::Theme* Theme;
    };
}