#pragma once

#include "ui/Color.h"
#include "ui/control/ClickableControl.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ClickResponseView:public ClickableControl {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        uint64_t startTime = 0;
        uint32_t length = 150;
        bool finishedAnimating = true;
        Color color;

    public:
        ClickResponseView(const Color& color = 0x3fffffff):color(color) {
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }

#pragma region property Color
        inline const Color& getColor() const {
            return color;
        }

        inline void setColor(const Color& color) {
            this->color = color;
        }
#pragma endregion

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