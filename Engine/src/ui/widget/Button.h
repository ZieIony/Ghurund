#pragma once

#include "ui/control/Stack.h"
#include "ui/control/ImageView.h"
#include "ui/control/Border.h"
#include "ui/control/TextView.h"
#include "ui/control/ClickableView.h"
#include "ui/control/Surface.h"
#include "ui/control/Clip.h"
#include "ui/control/PaddingContainer.h"

namespace Ghurund::UI {
    class Button :public ClickableView {
    private:
        Border* border;
        Clip* clip;
        Surface* background;
        Stack* stack, * stack2;
        PaddingContainer* container;

    public:
        Button();

        ~Button();

        inline void setContent(Control* control) {
            container->Child = control;
        }

        inline Control* getContent() {
            return container->Child;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        inline Padding const& getPadding() const {
            return container->Padding;
        }

        __declspec(property(get = getPadding)) Padding& Padding;

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

        inline float getCornerRadius() const {
            return border->CornerRadius;
        }

        inline void setCornerRadius(float radius) {
            border->CornerRadius = radius;
            clip->CornerRadius = radius;
        }

        __declspec(property(get = getCornerRadius, put = setCornerRadius)) float CornerRadius;

        inline float getBorderThickness() const {
            return border->Thickness;
        }

        inline void setBorderThickness(float thickness) {
            border->Thickness = thickness;
        }

        __declspec(property(get = getBorderThickness, put = setBorderThickness)) float BorderThickness;

        virtual void measure();
    };
}