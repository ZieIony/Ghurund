#pragma once

#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/RootView.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/Canvas.h"

#include "EditorWindowBinding.h"
#include "ui/font/FontLoader.h"
#include "ui/image/BitmapLoader.h"
#include "ui/image/ImageLoader.h"

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class EditorWindow:public ApplicationWindow {
    private:
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        EditorWindowBinding* binding;

    public:
        EditorWindow(Ghurund::Application& app, Renderer& renderer):ApplicationWindow(app, renderer) {
            Style = WindowStyle{
             .hasMinimizeButton = true,
             .hasMaximizeButton = true,
             .hasTitle = true,
             .borderStyle = WindowBorderStyle::RESIZE,
             .showOnTaskbar = true
            };
        }

        ~EditorWindow() {
            delete context;
            delete lightTheme;
            delete darkTheme;
        }

        virtual void init(WindowManager& windowManager) {
            __super::init(windowManager);

            /*
            auto fontLoader = ghnew FontLoader(*app.Graphics2D.DWriteFactory);
            fontLoader->init();
            app.ResourceManager.registerLoader(Font::TYPE, std::unique_ptr<FontLoader>(fontLoader));
            auto imageLoader = ghnew ImageLoader();
            imageLoader->init();
            app.ResourceManager.registerLoader(Image::TYPE, std::unique_ptr<ImageLoader>(imageLoader));
            auto bitmapLoader = ghnew BitmapLoader(*imageLoader, *app.Graphics2D.DeviceContext);
            app.ResourceManager.registerLoader(Bitmap::TYPE, std::unique_ptr<BitmapLoader>(bitmapLoader));

            lightTheme = ghnew LightTheme(*app.Graphics2D.DWriteFactory, app.ResourceManager);
            darkTheme = ghnew DarkTheme(*app.Graphics2D.DWriteFactory, app.ResourceManager);
            context = ghnew UIContext(*app.Graphics2D.DWriteFactory, *this, app.ResourceManager);

            layoutLoader = ghnew LayoutLoader(*app.Graphics2D.Factory, app.ResourceManager, *lightTheme);
            app.ResourceManager.registerLoader(Layout::TYPE, std::unique_ptr<LayoutLoader>(layoutLoader));

            rootView = ghnew Ghurund::UI::RootView(*context);

            SharedPointer<Layout> layout = app.ResourceManager.load<Layout>(FilePath(L"apps/Editor/res/EditorWindow.xml"), nullptr, LoadOption::DONT_CACHE);
            binding = ghnew EditorWindowBinding();
            binding->Theme = lightTheme;
            binding->Layout = std::make_unique<LayoutBinding>(layout->Controls[0]);
            rootView->Child = previewLayout;
            binding->ThemeChanged.add([this](PreviewLayout& previewLayout, ThemeType type) {
                updateTheme(type);
                return true;
            });

            Layers.add(std::unique_ptr<Layer>(ghnew UILayer(app.Graphics2D, rootView)));

            PointerList<Control*> controls;
            layoutLoader.load(L"Editor/res/EditorWindow.xml", controls);
            binding = ghnew EditorWindowBinding(controls[0]);
            rootView->Child = binding->Root;

            RootView = rootView;*/
        }
    };
}