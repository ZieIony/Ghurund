#include "ghuidxpch.h"
#include "DxUIFeature.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/DxGraphics.h"
#include <ui/control/Control.h>
#include <core/image/Image.h>
#include "ui/font/FontLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/loading/LayoutLoader.h"
#include <ui/loading/MaterialPropertyLoader.h>

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& DxUIFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxUIFeature::onInit() {
        drawableFactory = ghnew Ghurund::UI::DrawableFactory(resourceManager);
        textFormatFactory = ghnew Ghurund::UI::DirectX::TextFormatFactory();
        constraintFactory = ghnew Ghurund::UI::ConstraintFactory();

        auto fontLoader = makeIntrusive<FontLoader>();

        resourceManager.Loaders.set<Ghurund::UI::Font>(*fontLoader.get());

        layoutLoader = makeIntrusive<Ghurund::UI::LayoutLoader>(resourceManager, *drawableFactory, *textFormatFactory, *constraintFactory);
        layoutLoader->PropertyLoaders.add(std::make_unique<MaterialPropertyLoader>(resourceManager, materialFactory));
        resourceManager.Loaders.set<Control>(*layoutLoader.get());
    }
    
    void DxUIFeature::onUninit() {
        resourceManager.Loaders.remove<Control>();
        resourceManager.Loaders.remove<Ghurund::UI::Font>();
        layoutLoader.set(nullptr);
        delete drawableFactory;
        drawableFactory = nullptr;
        delete textFormatFactory;
        textFormatFactory = nullptr;
        delete constraintFactory;
        constraintFactory = nullptr;
    }
}
