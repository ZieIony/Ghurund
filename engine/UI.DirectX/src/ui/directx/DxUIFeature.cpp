#include "ghuidxpch.h"
#include "DxUIFeature.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/control/Control.h"
#include "ui/font/FontLoader.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/loading/MaterialPropertyLoader.h"
#include "engine/directx/texture/DxTextureFactory.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine::DirectX;

    const Ghurund::Core::Type& DxUIFeature::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<UIFeature>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxUIFeature::onInit() {
        commandList = makeIntrusive<CommandList>();
        // TODO: use CopyQueue, but first implement CommandList compatible with copy queue
		commandList->init(graphics, *graphics.DirectQueue);
        textureFactory = ghnew DxTextureFactory(graphics, commandList.ref());
        constraintFactory = ghnew Ghurund::UI::ConstraintFactory();

        auto fontLoader = makeIntrusive<FontLoader>();

        resourceManager.Loaders.set<Ghurund::UI::Font>(*fontLoader.get());

        layoutLoader = makeIntrusive<Ghurund::UI::LayoutLoader>(resourceManager, *textureFactory, *constraintFactory);
        layoutLoader->PropertyLoaders.add(std::make_unique<MaterialPropertyLoader>(resourceManager, *(MaterialLoader*)resourceManager.Loaders.get<IMaterial>()));
        resourceManager.Loaders.set<Control>(*layoutLoader.get());
    }
    
    void DxUIFeature::onUninit() {
        resourceManager.Loaders.remove<Control>();
        resourceManager.Loaders.remove<Ghurund::UI::Font>();
        layoutLoader.set(nullptr);
        delete textureFactory;
        textureFactory = nullptr;
        delete constraintFactory;
        constraintFactory = nullptr;
    }
}
