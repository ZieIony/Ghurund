#include "TestLevel.h"
#include "MathUtils.h"
#include "ui/gdi/GdiGui.h"
#include "ui/control/stack.h"
#include "ui/control/row.h"
#include "ui/widget/TextBorderButton.h"
#include "ui/control/Space.h"

class TestApplication:public Application {
private:
    Level* testLevel = nullptr;
    Stack *stack;
    Row *row;
    Canvas* canvas;
    Space *space;
    TextBorderButton*button, *button2;
    GdiGui gui;

    Font* font;
    ButtonStyle* pressedStyle;
    ButtonStyle* releasedStyle;

    std::function<void(Control&)> buttonStateHandler = [&](Control& control) {
        TextBorderButton& button = (TextBorderButton&)control;
        if (button.Pressed) {
            button.setStyle(*pressedStyle);
        } else {
            button.setStyle(*releasedStyle);
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

        font = ghnew GdiFont("Arial", 10);
        pressedStyle = ghnew ButtonStyle(0xb1000000, 0xde000000, font, ghnew ColorDrawable(0x2f000000));
        releasedStyle = ghnew ButtonStyle(0x61000000, 0xde000000, font, ghnew ColorDrawable(0x1f000000));

        button = ghnew TextBorderButton(*releasedStyle);
        button->setDesiredSize(80, 28);
        button->Text = "BUTTON";
        button->OnStateChanged.add(buttonStateHandler);

        space = ghnew Space();
        space->DesiredSize = XMFLOAT2(8, LayoutSize::MATCH_PARENT);

        button2 = ghnew TextBorderButton(*releasedStyle);
        button2->setDesiredSize(LayoutSize::WRAP_CONTENT, LayoutSize::WRAP_CONTENT);
        button2->Text = "BUTTON 2";
        button2->OnStateChanged.add(buttonStateHandler);

        row = ghnew Row();
        row->DesiredSize = XMFLOAT2(LayoutSize::WRAP_CONTENT, LayoutSize::WRAP_CONTENT);
        row->Children.add({ button, space, button2 });

        stack = ghnew Stack();
        stack->Children.add(row);
        stack->Gravity = { HorizontalGravity::CENTER, VerticalGravity::CENTER };

        Window.OnSizeChanged.add([this](Ghurund::Window& window) {
            stack->measure();
            stack->layout(0, 0, window.Size.x, window.Size.y);
            Window.refresh();
        });

        Window.OnKeyEvent.add([this](Ghurund::Window& window, const KeyEventArgs& args) {
            stack->dispatchKeyEvent(args);
        });

        Window.OnMouseButtonEvent.add([this](Ghurund::Window& window, const MouseButtonEventArgs& args) {
            stack->dispatchMouseButtonEvent(args);
        });

        Window.OnMouseMotionEvent.add([this](Ghurund::Window& window, const MouseMotionEventArgs& args) {
            stack->dispatchMouseMotionEvent(args);
        });

        Window.OnMouseWheelEvent.add([this](Ghurund::Window& window, const MouseWheelEventArgs& args) {
            stack->dispatchMouseWheelEvent(args);
        });

        Window.OnPaint.add([this](const Ghurund::Window &window) {
            canvas->beginPaint();
            canvas->clear(0xffe0e0e0);
            stack->draw(*canvas);
            canvas->endPaint();
        });
    }

    void onUninit() {
        gui.uninit();
        /*LevelManager.setLevel(nullptr);
        delete testLevel;*/
    }
};
