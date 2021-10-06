#include "ghpch.h"
#include "UIFeature.h"

#include "application/Application.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

namespace Ghurund {

    const Ghurund::Core::Type& UIFeature::GET_TYPE() {
        static auto PROPERTY_GRAPHICS2D = Ghurund::ReadOnlyProperty<UIFeature, Ghurund::Graphics2D&>("Graphics2D", (Ghurund::Graphics2D & (UIFeature::*)()) & getGraphics2D);
        static auto PROPERTY_THEME = Ghurund::Property<UIFeature, Ghurund::UI::Theme*>("Theme", (Ghurund::UI::Theme * (UIFeature::*)()) & getTheme, (void(UIFeature::*)(Ghurund::UI::Theme*)) & setTheme);

        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>("Ghurund", "UIFeature")
            .withProperty(PROPERTY_GRAPHICS2D)
            .withProperty(PROPERTY_THEME)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Status UIFeature::init() {
        graphics2d = ghnew Ghurund::Graphics2D();
        Status result = graphics2d->init(app.Graphics);
        if (result != Status::OK)
            return result;

        auto fontLoader = ghnew FontLoader(*graphics2d->DWriteFactory);
        result = fontLoader->init();
        if (result != Status::OK)
            return result;
        app.ResourceManager.Loaders.set<Font>(std::unique_ptr<FontLoader>(fontLoader));
        auto imageLoader = ghnew ImageLoader();
        result = imageLoader->init();
        if (result != Status::OK)
            return result;
        app.ResourceManager.Loaders.set<Image>(std::unique_ptr<ImageLoader>(imageLoader));
        auto bitmapLoader = ghnew BitmapLoader(*imageLoader, *graphics2d->DeviceContext);
        app.ResourceManager.Loaders.set<Bitmap>(std::unique_ptr<BitmapLoader>(bitmapLoader));
        auto layoutLoader = ghnew LayoutLoader(*graphics2d->Factory, app.ResourceManager);
        app.ResourceManager.Loaders.set<Layout>(std::unique_ptr<LayoutLoader>(layoutLoader));
        this->layoutLoader = (LayoutLoader*)app.ResourceManager.Loaders.get<Layout>();

        return Status::OK;
    }
    
    void UIFeature::uninit() {
        app.ResourceManager.Loaders.remove<Layout>();
        app.ResourceManager.Loaders.remove<Bitmap>();
        app.ResourceManager.Loaders.remove<Image>();
        app.ResourceManager.Loaders.remove<Font>();
        delete graphics2d;
        graphics2d = nullptr;
    }
}
