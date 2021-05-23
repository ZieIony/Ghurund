#pragma once

#include "ui/Color.h"
#include "ui/control/ClickableControl.h"

#include "reflection_145c55ab_4bd6_40a4_8a64_467ec3f3427c.h"

namespace Ghurund::UI {
    class ClickResponseView:public ClickableControl {
        reflection_145c55ab_4bd6_40a4_8a64_467ec3f3427c

    private:
        uint64_t startTime = 0;
        uint32_t length = 150;
        bool finishedAnimating = true;
        Color color;

    public:
        ClickResponseView(const Color& color = 0x3fffffff):color(color) {
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }

        inline const Color& getColor() const {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) const Ghurund::UI::Color& Color;

        virtual void onUpdate(const uint64_t time) override;

        virtual void onDraw(Canvas& canvas) override;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;
    };

    class ClickResponseViewOnBackgroundStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class ClickResponseViewOnAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}