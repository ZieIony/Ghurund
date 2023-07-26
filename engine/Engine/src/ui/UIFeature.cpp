#include "ghpch.h"
#include "UIFeature.h"

#include "ui/direct2d/Graphics2D.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/directx/Graphics.h"
#include <ui/control/Control.h>
#include <core/image/Image.h>
#include "ui/direct2d/font/FontLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"

namespace Ghurund {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    const Ghurund::Core::Type& UIFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(UIFeature))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void UIFeature::onInit() {
        shapeFactory = ghnew Ghurund::UI::Direct2D::ShapeFactory(graphics2d.D2DFactory);
        drawableFactory = ghnew Ghurund::UI::Direct2D::DrawableFactory(resourceManager);
        textFormatFactory = ghnew Ghurund::UI::Direct2D::TextFormatFactory();
        constraintFactory = ghnew Ghurund::UI::ConstraintFactory();

        auto fontLoader = makeShared<FontLoader>(graphics2d.DWriteFactory);
        fontLoader->init();

        resourceManager.Loaders.set<Ghurund::UI::Font>(fontLoader.get());

        auto bitmapLoader = makeShared<BitmapLoader>(*(ImageLoader*)resourceManager.Loaders.get<Image>(), graphics2d.DeviceContext);
        resourceManager.Loaders.set<Ghurund::UI::Bitmap>(bitmapLoader.get());
        layoutLoader = makeShared<Ghurund::UI::LayoutLoader>(resourceManager, *shapeFactory, *drawableFactory, *textFormatFactory, *constraintFactory);
        resourceManager.Loaders.set<Control>(layoutLoader.get());
    }
    
    void UIFeature::onUninit() {
        resourceManager.Loaders.remove<Control>();
        resourceManager.Loaders.remove<Ghurund::UI::Bitmap>();
        resourceManager.Loaders.remove<Image>();
        resourceManager.Loaders.remove<Ghurund::UI::Font>();
        layoutLoader.set(nullptr);
        delete shapeFactory;
        shapeFactory = nullptr;
        delete drawableFactory;
        drawableFactory = nullptr;
        delete textFormatFactory;
        textFormatFactory = nullptr;
        delete constraintFactory;
        constraintFactory = nullptr;
    }
}
