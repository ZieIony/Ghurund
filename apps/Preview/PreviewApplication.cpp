module;

#include "graphics/Renderer.h"

module Preview.PreviewApplication;

namespace Preview {
    PreviewApplication::PreviewApplication() {
        Features.add(makeShared<UIFeature>(*this).get());
        Features.add(makeShared<Graphics>().get());
        renderer = ghnew Ghurund::Renderer();
    }

    PreviewApplication::~PreviewApplication() {
        delete renderer;
    }

    void PreviewApplication::onInit() {
        ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
        ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));

        renderer->init(Features.get<Graphics>(), *parameterManager);

        auto window = ghnew PreviewWindow(*this, *renderer);
        window->title = _T("Preview");
        window->Size = { 800, 600 };
        Windows.add(window);
        window->visible = true;
        window->bringToFront();
    }
}
