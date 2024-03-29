﻿#include "PreviewWindow.h"
#include "ui/UIFeature.h"
#include "graphics/Renderer.h"

#include <format>

namespace Preview {
    class PreviewApplication:public Ghurund::Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;

    public:
        PreviewApplication() {
            Features.add(std::make_unique<UIFeature>(*this));
            Features.add(std::make_unique<Graphics>());
        }

        virtual void onInit() override {
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
            ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));

            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew PreviewWindow(*this, renderer);
            window->title = _T("Preview");
            window->Size = { Settings.get<uint32_t>("width"), Settings.get<uint32_t>("height") };
            Windows.add(window);
            window->visible = true;
            window->bringToFront();
        }
    };
}
