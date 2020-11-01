#pragma once

#include "TextBlock.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    class Theme;

    class TextBlockPrimaryStyle:public Style<TextBlock> {
    public:
        TextBlockPrimaryStyle(Theme& theme):Style<TextBlock>(theme) {}

        virtual void onStateChanged(TextBlock& textView) const override;
    };

    class TextBlockSecondaryStyle:public Style<TextBlock> {
    public:
        TextBlockSecondaryStyle(Theme& theme):Style<TextBlock>(theme) {}

        virtual void onStateChanged(TextBlock& textView) const override;
    };

    class TextBlockHeaderStyle:public Style<TextBlock> {
    public:
        TextBlockHeaderStyle(Theme& theme):Style<TextBlock>(theme) {}

        virtual void onStateChanged(TextBlock& textView) const override;
    };
}