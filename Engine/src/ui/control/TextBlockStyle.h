#pragma once

#include "TextBlock.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    class Theme;

    class TextBlockPrimaryStyle:public Style2<TextBlock> {
    public:
        virtual void onThemeChanged(TextBlock& textView) const override;

        virtual void onStateChanged(TextBlock& textView) const override;
    };

    class TextBlockSecondaryStyle:public Style2<TextBlock> {
    public:
        virtual void onThemeChanged(TextBlock& textView) const override;

        virtual void onStateChanged(TextBlock& textView) const override;
    };

    class TextBlockHeaderStyle:public Style2<TextBlock> {
    public:
        virtual void onThemeChanged(TextBlock& textView) const override;

        virtual void onStateChanged(TextBlock& textView) const override;
    };
}