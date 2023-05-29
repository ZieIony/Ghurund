﻿#include "graphics/Renderer.h"
#include "core/application/Application.h"

#include "PreviewWindow.h"
#include "ui/UIFeature.h"

#include <format>

namespace Preview {
    using namespace Ghurund;

    class PreviewApplication:public Ghurund::Application {
    protected:
        Ghurund::Renderer renderer;
        Ghurund::ParameterManager parameterManager;

    public:
        PreviewApplication() {
            Features.add(makeShared<UIFeature>(*this).get());
            Features.add(makeShared<Graphics>().get());
        }

        virtual void onInit() override {
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
            ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));

            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew PreviewWindow(*this, renderer);
            window->title = _T("Preview");
            window->Size = { 800, 600 };
            Windows.add(window);
            window->visible = true;
            window->bringToFront();
        }
    };
}
