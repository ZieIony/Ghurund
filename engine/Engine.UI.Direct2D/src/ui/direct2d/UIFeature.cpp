#include "ghuid2dpch.h"
#include "UIFeature.h"

#include "ui/direct2d/Graphics2D.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/directx/Graphics.h"
#include <ui/control/Control.h>
#include <core/image/Image.h>
#include "ui/font/FontLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"
#include "ui/direct2d/image/BitmapFactory.h"

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& UIFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>(Ghurund::UI::Direct2D::NAMESPACE_NAME, GH_STRINGIFY(UIFeature))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void UIFeature::onInit() {
        shapeFactory = ghnew Ghurund::UI::Direct2D::ShapeFactory(graphics2d.D2DFactory);
        drawableFactory = ghnew Ghurund::UI::Direct2D::DrawableFactory(resourceManager);
        textFormatFactory = ghnew Ghurund::UI::Direct2D::TextFormatFactory();
        constraintFactory = ghnew Ghurund::UI::ConstraintFactory();
        bitmapFactory = ghnew BitmapFactory(graphics2d.DeviceContext);

        auto fontLoader = makeIntrusive<FontLoader>(*bitmapFactory);

        resourceManager.Loaders.set<Ghurund::UI::Font>(fontLoader.get());

        auto bitmapLoader = makeIntrusive<BitmapLoader>(*(ImageLoader*)resourceManager.Loaders.get<Image>(), *bitmapFactory);
        resourceManager.Loaders.set<Ghurund::UI::Bitmap>(bitmapLoader.get());
        layoutLoader = makeIntrusive<Ghurund::UI::LayoutLoader>(resourceManager, *shapeFactory, *drawableFactory, *textFormatFactory, *constraintFactory);
        resourceManager.Loaders.set<Control>(layoutLoader.get());
    }
    
    void UIFeature::onUninit() {
        resourceManager.Loaders.remove<Control>();
        resourceManager.Loaders.remove<Ghurund::UI::Bitmap>();
        resourceManager.Loaders.remove<Image>();
        resourceManager.Loaders.remove<Ghurund::UI::Font>();
        layoutLoader.set(nullptr);
        delete bitmapFactory;
        bitmapFactory = nullptr;
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
