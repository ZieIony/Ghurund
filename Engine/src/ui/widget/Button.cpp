#include "Button.h"

namespace Ghurund::UI {
    Button::Button() {
        stack2 = ghnew Stack();
        {
            clip = ghnew Clip();
            {
                clip->CornerRadius = 0.0f;

                stack = ghnew Stack();
                {
                    background = ghnew Surface();
                    background->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);

                    container = ghnew PaddingContainer();
                    container->Padding.Vertical = 4;
                    container->Padding.Horizontal = 8;
                    container->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);

                    stack->Gravity = { Gravity::Horizontal::CENTER, Gravity::Vertical::CENTER };
                    stack->Children.add({ background, container });
                }
                clip->Child = stack;
            }

            border = ghnew Border();
            border->setPreferredSize(PreferredSize::Width::FILL, PreferredSize::Height::FILL);
            border->CornerRadius = 0.0f;

            stack2->Children.add({ clip, border });
        }
        Child = stack2;
    }
    
    Button::~Button() {
        container->release();
        stack->release();
        stack2->release();
        clip->release();
        border->release();
        background->release();
    }
    
    void Button::measure() {
        container->PreferredSize = PreferredSize;
        stack->PreferredSize = PreferredSize;
        stack2->PreferredSize = PreferredSize;
        clip->PreferredSize = PreferredSize;
        __super::measure();
    }
}