#pragma once

#include "application/Feature.h"
#include "ui/font/FontLoader.h"
#include "ui/image/BitmapLoader.h"
#include "ui/image/ImageLoader.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "graphics/Graphics2D.h"

namespace Ghurund {
    using namespace Ghurund::UI;

    class UIFeature:public Feature {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        Application& app;
        Ghurund::Graphics2D* graphics2d = nullptr;
        Theme* theme = nullptr;
        LayoutLoader* layoutLoader = nullptr;

    public:
        UIFeature(Application& app):app(app) {}

        virtual Status init() override;

        virtual void uninit() override;

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