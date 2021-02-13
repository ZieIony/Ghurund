#pragma once

#include "TextBlock.h"
#include "ui/style/Style.h"

namespace Ghurund::UI {
    class TextBlockButtonStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;

        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockPrimaryStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;

        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockSecondaryStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;

        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockHeaderStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override;

        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockButtonOnAccentStyle:public TextBlockButtonStyle {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockPrimaryOnAccentStyle:public TextBlockPrimaryStyle {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockSecondaryOnAccentStyle:public TextBlockSecondaryStyle {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class TextBlockHeaderOnAccentStyle:public TextBlockHeaderStyle {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}