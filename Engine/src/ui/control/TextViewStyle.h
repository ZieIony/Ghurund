#pragma once

#include "TextView.h"
#include "ui/Style.h"

namespace Ghurund::UI {
    class Theme;

    class TextViewPrimaryStyle:public Style<TextView> {
    public:
        TextViewPrimaryStyle(Theme& theme):Style<TextView>(theme) {}

        virtual void onStateChanged(TextView& textView) const override;
    };

    class TextViewSecondaryStyle:public Style<TextView> {
    public:
        TextViewSecondaryStyle(Theme& theme):Style<TextView>(theme) {}

        virtual void onStateChanged(TextView& textView) const override;
    };

    class TextViewHeaderStyle:public Style<TextView> {
    public:
        TextViewHeaderStyle(Theme& theme):Style<TextView>(theme) {}

        virtual void onStateChanged(TextView& textView) const override;
    };
}