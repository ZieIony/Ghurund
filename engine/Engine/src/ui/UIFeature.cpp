module;

#include "ui/direct2d/Graphics2D.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/directx/Graphics.h"
#include <ui/control/Control.h>
#include <core/image/Image.h>
#include "ui/direct2d/font/FontLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"
#include "ui/direct2d/loading/LayoutLoader.h"

module Ghurund.Engine.UI.UIFeature;

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    const Ghurund::Core::Type& UIFeature::GET_TYPE() {
        static auto PROPERTY_GRAPHICS2D = Property<UIFeature, Ghurund::UI::Direct2D::Graphics2D&>("Graphics2D", &getGraphics2D);

        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>(Ghurund::NAMESPACE_NAME, "UIFeature")
            .withProperty(PROPERTY_GRAPHICS2D)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void UIFeature::onInit() {
        graphics2d = ghnew Ghurund::UI::Direct2D::Graphics2D();
        Ghurund::Core::DirectX::Graphics& graphics = app.Features.get<Ghurund::Core::DirectX::Graphics>();
        graphics2d->init(*graphics.Device, *graphics.DirectQueue);
        shapeFactory = ghnew Ghurund::UI::Direct2D::ShapeFactory(*graphics2d->D2DFactory);
        imageDrawableFactory = ghnew Ghurund::UI::Direct2D::ImageDrawableFactory(app.ResourceManager);
        textFormatFactory = ghnew Ghurund::UI::Direct2D::TextFormatFactory();

        auto fontLoader = ghnew FontLoader(*graphics2d->DWriteFactory);
        fontLoader->init();

        auto imageLoader = ghnew ImageLoader();
        imageLoader->init();

        app.ResourceManager.Loaders.set<Ghurund::UI::Font>(std::unique_ptr<FontLoader>(fontLoader));
        app.ResourceManager.Loaders.set<Image>(std::unique_ptr<ImageLoader>(imageLoader));

        auto bitmapLoader = ghnew BitmapLoader(*imageLoader, graphics2d->DeviceContext);
        app.ResourceManager.Loaders.set<Ghurund::UI::Bitmap>(std::unique_ptr<BitmapLoader>(bitmapLoader));
        auto layoutLoader = ghnew Ghurund::UI::Direct2D::LayoutLoader(app.ResourceManager, *shapeFactory, *imageDrawableFactory, *textFormatFactory);
        app.ResourceManager.Loaders.set<Control>(std::unique_ptr<Ghurund::UI::Direct2D::LayoutLoader>(layoutLoader));
    }
    
    void UIFeature::onUninit() {
        app.ResourceManager.Loaders.remove<Control>();
        app.ResourceManager.Loaders.remove<Ghurund::UI::Bitmap>();
        app.ResourceManager.Loaders.remove<Image>();
        app.ResourceManager.Loaders.remove<Ghurund::UI::Font>();
        delete shapeFactory;
        shapeFactory = nullptr;
        delete imageDrawableFactory;
        imageDrawableFactory = nullptr;
        delete textFormatFactory;
        textFormatFactory = nullptr;
        delete graphics2d;
        graphics2d = nullptr;
    }
}
