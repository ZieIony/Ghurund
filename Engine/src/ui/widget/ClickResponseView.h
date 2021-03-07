#pragma once

#include "ui/Color.h"
#include "ui/control/ClickableControl.h"

namespace Ghurund::UI {
    class ClickResponseView:public ClickableControl {
    private:
        uint64_t startTime = 0;
        uint32_t length = 150;
        bool finishedAnimating = true;
        Color color;

    protected:
        static const Ghurund::Type& GET_TYPE();

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
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