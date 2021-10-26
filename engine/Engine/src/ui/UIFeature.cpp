#include "ghpch.h"
#include "UIFeature.h"

#include "application/Application.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

namespace Ghurund {

    const Ghurund::Core::Type& UIFeature::GET_TYPE() {
        static auto PROPERTY_GRAPHICS2D = Ghurund::ReadOnlyProperty<UIFeature, Ghurund::UI::Direct2D::Graphics2D&>("Graphics2D", (Ghurund::UI::Direct2D::Graphics2D & (UIFeature::*)()) & getGraphics2D);

        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>(Ghurund::UI::NAMESPACE_NAME, "UIFeature")
            .withProperty(PROPERTY_GRAPHICS2D)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void UIFeature::init() {
        graphics2d = ghnew Ghurund::UI::Direct2D::Graphics2D();
        graphics2d->init(*app.Graphics.Device, *app.Graphics.DirectQueue);
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
        auto layoutLoader = ghnew LayoutLoader(app.ResourceManager, *shapeFactory, *imageDrawableFactory, *textFormatFactory);
        app.ResourceManager.Loaders.set<Layout>(std::unique_ptr<LayoutLoader>(layoutLoader));
    }
    
    void UIFeature::uninit() {
        app.ResourceManager.Loaders.remove<Layout>();
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
