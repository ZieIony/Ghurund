#include "TestLevel.h"
#include "MathUtils.h"
#include "ui/gdi/GdiGui.h"
#include "ui/control/stack.h"
#include "ui/control/row.h"
#include "ui/widget/TextButton.h"
#include "ui/control/Space.h"
#include <ui\layout\LayoutInflater.h>
#include "ui/RootView.h"
#include "ui/control/ListView.h"
#include "StringObject.h"

#include "MaterialColors.h"

class TestApplication:public Application {
private:
    Level* testLevel = nullptr;
    RootView* rootView;
    Row *row;
    Canvas* canvas;
    Space *space;
    TextButton *button, *button2;
    GdiGui gui;

    List<StringObject*> items;
    ListView<StringObject*>* listView;

    Font* font;
    ::Material::Light* theme;

    std::function<void(Control&)> buttonStateHandler = [&](Control& control) {
        TextButton& button = (TextButton&)control;
        if (button.Pressed) {
            button.setBackgroundColor(theme->color_primary_dark);
        } else {
            button.setBackgroundColor(theme->color_primary);
        }
        Window.refresh();
    };

public:
    void onInit() {

        /*testLevel = ghnew TestLevel(*this);
        LevelManager.setLevel(testLevel);

        Renderer.ClearColor = &makeColor(0xff7f7f7f);*/

        gui.init();
        canvas = gui.makeCanvas(Window.Handle);

        theme = ghnew::Material::Light();
        font = ghnew Font("Arial", 36, 400, false);

        /*button = ghnew TextBorderButton(*releasedStyle);
        button->setPreferredSize(80, 28);
        button->Text = "BUTTON";
        button->OnStateChanged.add(buttonStateHandler);

        space = ghnew Space();
        space->PreferredSize = XMFLOAT2(8, MeasuredSize::FILL);

        button2 = ghnew TextBorderButton(*releasedStyle);
        button2->setPreferredSize(MeasuredSize::WRAP, MeasuredSize::WRAP);
        button2->Text = "BUTTON 2";
        button2->OnStateChanged.add(buttonStateHandler);

        row = ghnew Row();
        row->PreferredSize = XMFLOAT2(MeasuredSize::WRAP, MeasuredSize::WRAP);
        row->Children.add({ button, space, button2 });

        stack = ghnew Stack();
        stack->Children.add(row);
        stack->Gravity = { Gravity::Horizontal::CENTER, Gravity::Vertical::CENTER };*/

        LayoutInflater inflater;
        rootView = ghnew RootView(Window);

        /*File file(_T("D:/projekty/GhurundEngine12/test.layout"));
        file.read();
        ASCIIString jsonString((char*)file.Data, file.Size);*/

        
        Gdiplus::Image* image = Gdiplus::Image::FromFile(L"D:/projekty/GuideToCustomViews/images/landscapedrawable.png");
        items.add(ghnew StringObject("Foxy fox", "Jumps over big fence"));
        items.add(ghnew StringObject("Ósemka", _T("¹¿ŸæóÊ123-~,.;")));
        items.add(ghnew StringObject("Strawberry", "Cherry and a rainbow"));
        items.add(ghnew StringObject("Melon", "Best fruit ever"));
        items.add(ghnew StringObject("Blueberry", "Greenberry"));
        items.add(ghnew StringObject("Watermelon", "Noice"));
        items.add(ghnew StringObject("Apple", "Android"));
        items.add(ghnew StringObject("Pear", "Deer"));
        items.add(ghnew StringObject("Plum", "Splash"));
        items.add(ghnew StringObject("Orange", "A color or a fruit?"));
        items.add(ghnew StringObject("Banana", "Mana mana"));
        items.add(ghnew StringObject("Beer", "Dark, with honey"));
        items.add(ghnew StringObject("Lemon", "Tree"));
        listView = ghnew ListView<StringObject*>();
        listView->items = items;
        listView->addAdapter(ghnew StringItemAdapter(theme, image));

        ScopedPointer<Row> row = ghnew Row();
        ScopedPointer<Stack> stack = ghnew Stack();
        ScopedPointer<ImageView> iv = ghnew ImageView();
        iv->PreferredSize.width = PreferredSize::Width(200);
        iv->PreferredSize.height = PreferredSize::Height(200);
        iv->Image = font->atlas;
        stack->Children.add(iv);
        row->Children.add({ listView, stack });
        rootView->Child = row;// inflater.load(jsonString);
        
        Window.OnSizeChanged.add([this](Ghurund::Window& window) {
            rootView->measure();
            rootView->layout(0, 0, window.Size.x, window.Size.y);
            Window.refresh();
        });

        Window.OnKeyEvent.add([this](Ghurund::Window& window, const KeyEventArgs& args) {
            rootView->dispatchKeyEvent(args);
        });

        Window.OnMouseButtonEvent.add([this](Ghurund::Window& window, const MouseButtonEventArgs& args) {
            rootView->dispatchMouseButtonEvent(args);
        });

        Window.OnMouseMotionEvent.add([this](Ghurund::Window& window, const MouseMotionEventArgs& args) {
            rootView->dispatchMouseMotionEvent(args);
        });

        Window.OnMouseWheelEvent.add([this](Ghurund::Window& window, const MouseWheelEventArgs& args) {
            rootView->dispatchMouseWheelEvent(args);
        });

        Window.OnPaint.add([this](const Ghurund::Window &window) {
            canvas->beginPaint();
            canvas->clear(theme->getColorBackground());
            rootView->draw(*canvas);
            canvas->endPaint();
        });
    }

    void onUninit() {
        items.deleteItems();
        listView->release();
        rootView->release();
        font->release();
        delete theme;
        delete canvas;
        rootView->release();

        gui.uninit();
        /*LevelManager.setLevel(nullptr);
        delete testLevel;*/
    }
};
