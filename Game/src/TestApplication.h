#include "MathUtils.h"
#include "ui/gdi/GdiGui.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/button/TextButton.h"
#include "ui/widget/button/ImageButton.h"
#include "ui/control/Space.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "core/ScopedPointer.h"
#include "ui/widget/menu/MenuItem.h"
#include "ui/widget/menu/Toolbar.h"
#include "ui/widget/menu/MenuBar.h"
#include "ui/widget/tab/TabContainer.h"
#include "ui/widget/SplitLayout.h"
#include "TestRecycler.h"
#include "tool/LogPanel.h"
#include "TestControls.h"
#include "ui/widget/menu/PopupMenu.h"
#include "TestImageViews.h"
#include "TestFlowLayouts.h"
#include "LayoutEditorTab.h"
#include "DragTestTab.h"
#include "WindowsTestTab.h"
#include "audio/Sound.h"

#include "MaterialColors.h"

using namespace Ghurund;
using namespace Ghurund::Editor;

static const unsigned int FRAME_COUNT = 3;

import Module;

class TestApplication:public Application {
private:
    GdiGui gui;

    ::Material::Theme* theme;
    ::Material::Theme* menuTheme;
    ModuleTest test;

public:
    void onInit() {

        /*testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);

        Renderer.ClearColor = &makeColor(0xff7f7f7f);*/

        gui.init();

        SystemWindow* window = nullptr;
        if (Settings.windowed) {
            window = ghnew OverlappedWindow();
        } else {
            window = ghnew FullscreenWindow();
        }

        window->initParameters(ParameterManager);

        window->OnSizeChanged.add([&](Ghurund::Window& window) {
            //swapChain->resize(args.width, args.height);
            return true;
        });

        window->Size = { Settings.width, Settings.height };
        /*SwapChain* swapChain = ghnew SwapChain();
        swapChain->init(Graphics, *window, FRAME_COUNT);
        window->SwapChain = swapChain;*/

        Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::GdiCanvas(window->Handle);
        ScopedPointer<Ghurund::UI::RootView> rootView = ghnew Ghurund::UI::RootView(*window, canvas);
        rootView->BackgroundColor = 0xffffffff;
        window->RootView = rootView;
        Windows.add(window);

        theme = ghnew::Material::Light(0xff0078D7);
        menuTheme = ghnew::Material::Light(0xff0078D7);

        ScopedPointer<ToolWindow> logWindow = ghnew ToolWindow(*theme);
        ScopedPointer<LogPanel> logPanel = ghnew LogPanel(*theme);
        logWindow->Content = logPanel;
        logWindow->Title = "Logs";
        /*Logger::init(ghnew CallbackLogOutput([this](LogType type, const tchar* log) {
            logPanel->addLog(type, copyStr(log));
            logPanel->repaint();
        }));*/

        ScopedPointer<ColorView> redSurface = ghnew ColorView(0xffff0000);
        SplitLayoutPtr splitLayout = ghnew SplitLayout(Orientation::VERTICAL);
        splitLayout->Child1 = redSurface;
        splitLayout->Child2 = logWindow;

        ScopedPointer<TestRecycler> testRecycler = ghnew TestRecycler(*theme);
        testRecycler->Name = "test recycler";

        ScopedPointer<TestImageViews> testImageViews = ghnew TestImageViews(*theme);
        ScopedPointer<TestFlowLayouts> testFlowLayouts = ghnew TestFlowLayouts(*theme);

        ScopedPointer<TabContainer> tabLayout = ghnew TabContainer(*theme);
        tabLayout->Name = "tabs";

        ScopedPointer<TestControls> column = ghnew TestControls(*theme, ResourceManager, ResourceContext);
        column->Name = "controls tab";

        ScopedPointer<LayoutEditorTab> layoutEditor = ghnew LayoutEditorTab(*theme);
        ScopedPointer<DragTestTab> dragTestTab = ghnew DragTestTab(*theme);
        ScopedPointer<WindowsTestTab> windowsTestTab = ghnew WindowsTestTab(*theme);

        tabLayout->Tabs = {
            ghnew TextTabItem("RecyclerView", testRecycler),
            ghnew TextTabItem("ImageViews", testImageViews),
            ghnew TextTabItem("testFlowLayouts", testFlowLayouts),
            ghnew TextTabItem("controls", column),
            ghnew TextTabItem("SplitLayout", splitLayout),
            ghnew TextTabItem("layout editor", layoutEditor),
            ghnew TextTabItem("drag test", dragTestTab),
            ghnew TextTabItem("windows test", windowsTestTab)
        };
        ((TabContainerLayout&)tabLayout->Layout).TabContainer->Adapters.clear();
        ((TabContainerLayout&)tabLayout->Layout).TabContainer->Adapters.add(ghnew TextTabItemAdapter(*tabLayout, *theme));
        tabLayout->SelectedPosition = 0;

        ScopedPointer<VerticalLayout> mainColumn = ghnew VerticalLayout();
        {
            Gdiplus::Image* copyIcon = new Gdiplus::Image(L"icons/copy 18.png");
            Gdiplus::Image* cutIcon = new Gdiplus::Image(L"icons/cut 18.png");
            Gdiplus::Image* pasteIcon = new Gdiplus::Image(L"icons/paste 18.png");

            MenuBarPtr menuBar = ghnew MenuBar(*menuTheme);
            menuBar->Name = "menu bar";
            menuBar->Items = {
                ghnew ButtonMenuItem("File", [](Control&) {
                    Logger::log(LogType::INFO, "File clicked\n");
                }),
                ghnew ButtonMenuItem("Edit", [this](Control& sender) {
                    Logger::log(LogType::INFO, "Edit clicked\n");
                    Gdiplus::Image* copyIcon = new Gdiplus::Image(L"icons/copy 18.png");
                    Gdiplus::Image* cutIcon = new Gdiplus::Image(L"icons/cut 18.png");
                    Gdiplus::Image* pasteIcon = new Gdiplus::Image(L"icons/paste 18.png");
                    PopupMenu* menu = ghnew PopupMenu(*menuTheme, *Windows[0]);
                    menu->Items = {
                        ghnew ButtonMenuItem("Undo", [](Control&) {
                            Logger::log(LogType::INFO, "undo clicked\n");
                        }),
                        ghnew ButtonMenuItem("Redo", [](Control&) {
                            Logger::log(LogType::INFO, "redo clicked\n");
                        }),
                        ghnew SeparatorMenuItem(),
                        ghnew ButtonMenuItem(copyIcon, "Copy", [](Control&) {
                            Logger::log(LogType::INFO, "copy clicked\n");
                        }),
                        ghnew ButtonMenuItem(cutIcon, "Cut", [](Control&) {
                            Logger::log(LogType::INFO, "cut clicked\n");
                        }),
                        ghnew ButtonMenuItem(pasteIcon, "Paste", [](Control&) {
                            Logger::log(LogType::INFO, "paste clicked\n");
                        })
                    };
                    auto pos = sender.PositionOnScreen;
                    menu->Window->Position = { (LONG)pos.x, (LONG)(pos.y + sender.Size.height) };
                    menu->Visible = true;
                }),
                ghnew ButtonMenuItem(_T("Help"), [](Control&) {
                    Logger::log(LogType::INFO, "Help clicked\n");
                })
            };

            ScopedPointer<Toolbar> toolbar = ghnew Toolbar(*theme);
            toolbar->Name = "toolbar";
            toolbar->Items = {
                ghnew ButtonMenuItem(copyIcon, "copy", [](Control&) {
                    Logger::log(LogType::INFO, "copy clicked\n");
                }),
                ghnew ButtonMenuItem(cutIcon, "cut", [](Control&) {
                    Logger::log(LogType::INFO, "cut clicked\n");
                }),
                ghnew ButtonMenuItem(pasteIcon, "paste", [](Control&) {
                    Logger::log(LogType::INFO, "paste clicked\n");
                })
            };

            ScopedPointer<ColorView> statusBar = ghnew ColorView();
            statusBar->Name = "status bar";
            statusBar->PreferredSize.height = 24;

            mainColumn->Children = { menuBar, toolbar, tabLayout, statusBar };
        }
        rootView->Child = mainColumn;
        rootView->invalidate();

        window->Visible = true;
        window->activate();
    }

    void onUninit() {
        delete theme;
        delete menuTheme;

        gui.uninit();
        /*LevelManager.setLevel(nullptr);
        delete testLevel;*/
    }
};
