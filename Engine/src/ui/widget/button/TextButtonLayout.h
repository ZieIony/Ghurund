#pragma once

#include "ButtonLayout.h"
#include "ui/control/ClickableView.h"
#include "ui/layout/StackLayout.h"
#include "ui/mixin/TextMixin.h"
#include "ui/mixin/BackgroundMixin.h"
#include "ui/mixin/BorderMixin.h"
#include "ui/mixin/PaddingMixin.h"
#include "ui/widget/ClickResponseView.h"

namespace Ghurund::UI {

    class LayoutLoader;

    class TextButtonLayout:public ButtonLayout, public TextLayoutMixin {
    public:
        virtual ~TextButtonLayout() = 0 {}
    };

    class TextButtonDefaultLayout:public TextButtonLayout, public BackgroundLayoutMixin, public PaddingLayoutMixin {
    private:
        SharedPointer<StackLayout> stack;
        SharedPointer<Border> border;
        SharedPointer<Clip> clip;
        SharedPointer<Shadow> shadow;

    protected:
        SharedPointer<ClickResponseView> clickResponseView;

    public:
        TextButtonDefaultLayout(ResourceContext& context, LayoutLoader& loader);

        virtual void onThemeChanged(Control& control) override;

        virtual void onStateChanged(Control& control) override;
    };

    class TextButtonFlatLayout:public TextButtonLayout, public BackgroundLayoutMixin, public PaddingLayoutMixin {
    private:
        SharedPointer<StackLayout> stack;
        SharedPointer<Border> border;
        SharedPointer<Clip> clip;

    protected:
        SharedPointer<ClickResponseView> clickResponseView;

    public:
        TextButtonFlatLayout(ResourceContext& context, LayoutLoader& loader);

        virtual void onThemeChanged(Control& control) override;

        virtual void onStateChanged(Control& control) override;
    };

    class TextButtonAccentLayout:public TextButtonLayout, public BackgroundLayoutMixin, public PaddingLayoutMixin {
    private:
        SharedPointer<StackLayout> stack;
        SharedPointer<Clip> clip;
        SharedPointer<Shadow> shadow;

    protected:
        SharedPointer<ClickResponseView> clickResponseView;

    public:
        TextButtonAccentLayout(ResourceContext& context, LayoutLoader& loader);

        virtual void onThemeChanged(Control& control) override;

        virtual void onStateChanged(Control& control) override;
    };

}