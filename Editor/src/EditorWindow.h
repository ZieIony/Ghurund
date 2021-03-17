#pragma once

#include "application/SystemWindow.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "ui/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/Canvas.h"

#include "EditorWindowBinding.h"

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class EditorWindow:public OverlappedWindow {
    private:
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        EditorWindowBinding* binding;
        LayoutLoader layoutLoader;
        Application* app;

    public:
        EditorWindow(Application& app):OverlappedWindow(app.Timer) {
            this->app = &app;
            Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
            swapChain->init(app.Graphics, &app.Graphics2D, *this);
            SwapChain = swapChain;

            lightTheme = ghnew LightTheme(app.ResourceContext, 0xff0078D7);
            darkTheme = ghnew DarkTheme(app.ResourceContext, 0xff0078D7);
            layoutLoader.init(*lightTheme, app.ResourceContext);
            context = ghnew UIContext(app.Graphics2D, *this, layoutLoader);

            Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
            canvas->init(app.Graphics2D);
            auto rootView = makeShared<Ghurund::UI::RootView>(*context, *canvas);
            rootView->Theme = lightTheme;
            rootView->BackgroundColor = lightTheme->Colors[Theme::COLOR_BACKGR0UND];

            PointerList<Control*> controls;
            layoutLoader.load(L"Editor/res/EditorWindow.xml", controls);
            binding = ghnew EditorWindowBinding(controls[0]);
            rootView->Child = binding->Root;

            RootView = rootView;
        }

        ~EditorWindow() {
            RootView = nullptr;
            delete context;
            delete lightTheme;
            delete darkTheme;
        }
    };
}