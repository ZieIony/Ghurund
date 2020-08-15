#pragma once

#include "ui/control/Stack.h"
#include "ui/control/ImageView.h"
#include "ui/control/Border.h"
#include "ui/control/TextView.h"
#include "ui/control/ClickableView.h"
#include "ui/control/Surface.h"
#include "ui/control/Clip.h"

namespace Ghurund::UI {
    class Button :public ClickableView {
    private:
        Border* border;
        Clip* clip;
        Surface* background;
        Stack* stack, * stack2;
        ControlContainer* container;

    public:
        Button() {
            stack2 = ghnew Stack();
            {
                clip = ghnew Clip();
                {
                    clip->CornerRadius = 2.0f;

                    stack = ghnew Stack();
                    {
                        background = ghnew Surface();
                        background->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);

                        container = ghnew ControlContainer();
                        container->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);

                        stack->Gravity = { Gravity::Horizontal::CENTER, Gravity::Vertical::CENTER };
                        stack->Children.add({ background, container });
                    }
                    clip->Child = stack;
                }

                border = ghnew Border();
                border->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);
                border->CornerRadius = 2.0f;

                stack2->Children.add({ clip, border });
            }
            Content = stack2;
        }

        ~Button() {
            container->release();
            stack->release();
            stack2->release();
            clip->release();
            border->release();
            background->release();
        }

        inline void setContent(Control* control) {
            container->Child = control;
        }

        inline Control* getContent() {
            return container->Child;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        inline unsigned int getBorderColor() const {
            return border->Color;
        }

        inline void setBorderColor(unsigned int color) {
            border->Color = color;
        }

        __declspec(property(get = getBorderColor, put = setBorderColor)) unsigned int BorderColor;

        void setBackgroundColor(unsigned int drawable) {
            background->color = drawable;
        }

        unsigned int getBackgroundColor() {
            return background->color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) unsigned int BackgroundColor;

        inline float getBorderThickness() const {
            return border->Thickness;
        }

        inline void setBorderThickness(float thickness) {
            border->Thickness = thickness;
        }

        __declspec(property(get = getBorderThickness, put = setBorderThickness)) float BorderThickness;

        virtual void measure() {
            container->PreferredSize = PreferredSize;
            stack->PreferredSize = PreferredSize;
            stack2->PreferredSize = PreferredSize;
            clip->PreferredSize = PreferredSize;
            __super::measure();
        }
    };
}