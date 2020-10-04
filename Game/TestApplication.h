#include "MathUtils.h"
#include "ui/gdi/GdiGui.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/LinearLayout.h"
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
#include "ui/widget/tab/TabContainerStyle.h"
#include "ui/widget/SplitLayout.h"
#include "TestRecycler.h"
#include "LogPanel.h"
#include "TestControls.h"
#include "ui/widget/menu/PopupMenu.h"
#include "TextImageViews.h"
#include "TestFlowLayouts.h"

#include "MaterialColors.h"

using namespace Ghurund;
using namespace Ghurund::Editor;

class TestApplication:public Application {
private:
    RootView* rootView;
    Canvas* canvas;
    GdiGui gui;
    LogPanel* logPanel;

    ::Material::Theme* theme;
    ::Material::Theme* menuTheme;

public:
    void onInit() {

        /*testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);

        Renderer.ClearColor = &makeColor(0xff7f7f7f);*/

        gui.init();
        canvas = gui.makeCanvas(Window.Handle);

        theme = ghnew::Material::Light(0xff0078D7);
        menuTheme = ghnew::Material::Light(0xff0078D7);

        rootView = ghnew RootView(Window);

        logPanel = ghnew LogPanel(*theme);
        /*Logger::init(ghnew CallbackLogOutput([this](LogType type, const tchar* log) {
            logPanel->addLog(type, copyStr(log));
            logPanel->repaint();
        }));*/

        ColorViewPtr redSurface = ghnew ColorView(0xffff0000);
        SplitLayoutPtr splitLayout = ghnew SplitLayout(Orientation::VERTICAL);
        splitLayout->Child1 = redSurface;
        splitLayout->Child2 = logPanel;

        ScopedPointer<TestRecycler> testRecycler = ghnew TestRecycler(*theme);
        testRecycler->Name = "test recycler";

        ScopedPointer<TestImageViews> testImageViews = ghnew TestImageViews(*theme);
        ScopedPointer<TestFlowLayouts> testFlowLayouts = ghnew TestFlowLayouts(*theme);

        ScopedPointer<TabContainer> tabLayout = ghnew TabContainer(theme->tabContainerStyle);
        tabLayout->Name = "tabs";

        ScopedPointer<TestControls> column = ghnew TestControls(*theme);
        column->Name = "controls tab";

        tabLayout->Tabs.addAll({
            ghnew TextTabItem("RecyclerView", testRecycler),
            ghnew TextTabItem("ImageViews", testImageViews),
            ghnew TextTabItem("testFlowLayouts", testFlowLayouts),
            ghnew TextTabItem("controls", column),
            ghnew TextTabItem("SplitLayout", splitLayout)
            });
        ((TabContainerLayout&)tabLayout->Layout).TabContainer->Adapters.clear();
        ((TabContainerLayout&)tabLayout->Layout).TabContainer->Adapters.add(ghnew TextTabItemAdapter(*tabLayout, *theme));
        tabLayout->SelectedPosition = 0;

        VerticalLayoutPtr mainColumn = ghnew VerticalLayout();
        {
            ImagePtr copyIcon = ghnew GdiImage(L"icons/copy 18.png");
            ImagePtr cutIcon = ghnew GdiImage(L"icons/cut 18.png");
            ImagePtr pasteIcon = ghnew GdiImage(L"icons/paste 18.png");

            MenuBarPtr menuBar = ghnew MenuBar(menuTheme->menuBarStyle);
            menuBar->Name = "menu bar";
            menuBar->Items.addAll({
                ghnew ButtonMenuItem("File", [](Control&) {
                    Logger::log(LogType::INFO, "File clicked\n");
                }),
                ghnew ButtonMenuItem("Edit", [this](Control& sender) {
                    Logger::log(LogType::INFO, "Edit clicked\n");
                    ScopedPointer<GdiImage> copyIcon = ghnew GdiImage(L"icons/copy 18.png");
                    ScopedPointer<GdiImage> cutIcon = ghnew GdiImage(L"icons/cut 18.png");
                    ScopedPointer<GdiImage> pasteIcon = ghnew GdiImage(L"icons/paste 18.png");
                    PopupMenu* menu = ghnew PopupMenu(*menuTheme, Window);
                    menu->Items.addAll({
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
                    });
                    auto pos = sender.PositionOnScreen;
                    menu->Window->Position = { (LONG)pos.x, (LONG)(pos.y + sender.Size.height) };
                    menu->Visible = true;
                }),
                ghnew ButtonMenuItem(_T("Help"), [](Control&) {
                    Logger::log(LogType::INFO, "Help clicked\n");
                })
            });

            ScopedPointer<Toolbar> toolbar = ghnew Toolbar(theme->toolbarStyle);
            toolbar->Name = "toolbar";
            toolbar->Items.addAll({
                ghnew ButtonMenuItem(copyIcon, "copy", [](Control&) {
                    Logger::log(LogType::INFO, "copy clicked\n");
                }),
                ghnew ButtonMenuItem(cutIcon, "cut", [](Control&) {
                    Logger::log(LogType::INFO, "cut clicked\n");
                }),
                ghnew ButtonMenuItem(pasteIcon, "paste", [](Control&) {
                    Logger::log(LogType::INFO, "paste clicked\n");
                })
                });

            ScopedPointer<ColorView> statusBar = ghnew ColorView();
            statusBar->Name = "status bar";
            statusBar->PreferredSize.height = 24;

            mainColumn->Children = { menuBar, toolbar, tabLayout, statusBar };
        }
        rootView->Child = mainColumn;

        Window.OnSizeChanged.add([this](Ghurund::Window& window) {
            rootView->invalidate();
            return true;
        });

        Window.OnKeyEvent.add([this](Ghurund::Window& window, const KeyEventArgs& args) {
            rootView->dispatchKeyEvent(args);
            return true;
        });

        Window.OnMouseButtonEvent.add([this](Ghurund::Window& window, const MouseButtonEventArgs& args) {
            rootView->dispatchMouseButtonEvent(args);
            return true;
        });

        Window.OnMouseMotionEvent.add([this](Ghurund::Window& window, const MouseMotionEventArgs& args) {
            rootView->dispatchMouseMotionEvent(args);
            return true;
        });

        Window.OnMouseWheelEvent.add([this](Ghurund::Window& window, const MouseWheelEventArgs& args) {
            rootView->dispatchMouseWheelEvent(args);
            return true;
        });

        Window.OnPaint.add([this](const Ghurund::Window& window) {
            canvas->beginPaint();
            canvas->clear(theme->getColorBackground());
            rootView->draw(*canvas);
            canvas->endPaint();
            return true;
        });

        Window.OnDestroy.add([this](const Ghurund::Window& window) {
            quit();
            return true;
        });

        Window.OnSizeChanged();
    }

    void onUninit() {
        rootView->release();
        delete theme;
        delete menuTheme;
        delete canvas;
        logPanel->release();

        gui.uninit();
        /*LevelManager.setLevel(nullptr);
        delete testLevel;*/
    }
};
