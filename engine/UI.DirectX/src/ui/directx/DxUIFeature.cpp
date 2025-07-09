#include "ghuidxpch.h"
#include "DxUIFeature.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/Graphics.h"
#include <ui/control/Control.h>
#include <core/image/Image.h>
#include "ui/font/FontLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/directx/image/BitmapLoader.h"
#include "ui/directx/image/BitmapFactory.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& DxUIFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxUIFeature::onInit() {
        shapeFactory = ghnew Ghurund::UI::DirectX::ShapeFactory();
        drawableFactory = ghnew Ghurund::UI::DrawableFactory(resourceManager);
        textFormatFactory = ghnew Ghurund::UI::DirectX::TextFormatFactory();
        constraintFactory = ghnew Ghurund::UI::ConstraintFactory();
        bitmapFactory = ghnew Ghurund::UI::DirectX::BitmapFactory();

        auto fontLoader = makeIntrusive<FontLoader>(*bitmapFactory);

        resourceManager->Loaders->set<Ghurund::UI::Font>(fontLoader.get());

        auto bitmapLoader = makeIntrusive<BitmapLoader>(*(ImageLoader*)resourceManager->Loaders->get<Image>(), *bitmapFactory);
        resourceManager->Loaders->set<Ghurund::UI::Bitmap>(bitmapLoader.get());
        layoutLoader = makeIntrusive<Ghurund::UI::LayoutLoader>(resourceManager, *shapeFactory, *drawableFactory, *textFormatFactory, *constraintFactory);
        resourceManager->Loaders->set<Control>(layoutLoader.get());
    }
    
    void DxUIFeature::onUninit() {
        resourceManager->Loaders->remove<Control>();
        resourceManager->Loaders->remove<Ghurund::UI::Bitmap>();
        resourceManager->Loaders->remove<Image>();
        resourceManager->Loaders->remove<Ghurund::UI::Font>();
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
