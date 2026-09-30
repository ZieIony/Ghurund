#include "DemoApplication.h"

namespace Demo {
    void DemoApplication::uninitDemoApplication() {
        delete renderer;
        renderer = nullptr;
        delete window;
        window = nullptr;

        delete textureFactory;
        delete theme;
        commandList.set(nullptr);
    }
    
    void DemoApplication::onInit() {
        auto graphicsFeature = Features.get<DxGraphicsFeature>();
        renderer = ghnew DxRenderer(graphicsFeature->Graphics);
        renderer->init();

        commandList = makeIntrusive<CommandList>();
        commandList->init(graphicsFeature->Graphics, *graphicsFeature->Graphics.CopyQueue);
        textureFactory = ghnew DxTextureFactory(graphicsFeature->Graphics, commandList.ref());
        theme = ghnew LightTheme(ResourceManager);

        window = ghnew DemoWindow(*this, *renderer, *textureFactory);
        window->init();

        window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void DemoApplication::onUninit() {
        uninitDemoApplication();
        __super::onUninit();
    }
}
