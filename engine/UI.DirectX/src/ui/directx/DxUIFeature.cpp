#include "ghuidxpch.h"
#include "DxUIFeature.h"

#include "core/reflection/TypeBuilder.h"
#include "engine/directx/texture/DxTextureFactory.h"
#include "ui/control/Control.h"
#include "ui/font/FontAtlasLoader.h"
#include "ui/font/FontLoader.h"
#include "ui/font/TextStyleLoader.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/material/UIMaterialPropertyLoader.h"
#include "ui/material/UIMaterialLoader.h"

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
        auto fontAtlasLoader = makeIntrusive<FontAtlasLoader>(resourceManager);
        resourceManager.Loaders.set<FontAtlas>(fontAtlasLoader.ref());
        auto textStyleLoader = makeIntrusive<TextStyleLoader>(resourceManager, fontAtlasLoader.ref());
        resourceManager.Loaders.set<TextStyle>(textStyleLoader.ref());

        auto materialLoader = makeIntrusive<UIMaterialLoader>(resourceManager, memoryManager);
        resourceManager.Loaders.set<UIMaterial>(materialLoader.ref());

        layoutLoader = makeIntrusive<Ghurund::UI::LayoutLoader>(resourceManager, *constraintFactory);
        layoutLoader->PropertyLoaders.add(std::make_unique<UIMaterialPropertyLoader>(resourceManager, materialLoader.ref()));
        resourceManager.Loaders.set<Control>(layoutLoader.ref());
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
