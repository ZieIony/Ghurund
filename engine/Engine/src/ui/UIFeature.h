#pragma once

#include "core/application/Feature.h"
#include "core/image/ImageLoader.h"
#include "ui/direct2d/font/FontLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/direct2d/Graphics2D.h"
#include "ui/direct2d/loading/ShapeFactory.h"
#include "ui/direct2d/loading/ImageDrawableFactory.h"
#include "ui/direct2d/loading/TextFormatFactory.h"

namespace Ghurund::Core {
    class Application;
}

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

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
        Ghurund::UI::Direct2D::Graphics2D* graphics2d = nullptr;
        Ghurund::UI::Direct2D::ShapeFactory* shapeFactory = nullptr;
        Ghurund::UI::Direct2D::ImageDrawableFactory* imageDrawableFactory = nullptr;
        Ghurund::UI::Direct2D::TextFormatFactory* textFormatFactory = nullptr;

    public:
        UIFeature(Application& app):app(app) {}

        virtual void onInit() override;

        virtual void onUninit() override;

        inline Ghurund::UI::Direct2D::Graphics2D& getGraphics2D() {
            return *graphics2d;
        }

        __declspec(property(get = getGraphics2D)) Ghurund::UI::Direct2D::Graphics2D& Graphics2D;
    };
}