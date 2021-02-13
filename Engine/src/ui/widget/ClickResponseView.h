#pragma once

#include "ui/control/ClickableControl.h"

namespace Ghurund::UI {
    class ClickResponseView:public ClickableControl {
    private:
        uint64_t startTime = 0;
        uint32_t length = 150;
        Paint paint;
        bool finishedAnimating = true;
        uint32_t color;

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<ClickResponseView>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ClickResponseView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        ClickResponseView(uint32_t color = 0x3fffffff) {
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            this->color = color;
        }

        inline uint32_t getColor() const {
            return color;
        }

        inline void setColor(uint32_t color) {
            this->color = color;
        }

        __declspec(property(get = getColor, put = setColor)) uint32_t Color;

        virtual void onUpdate(const uint64_t time) override;

        virtual void onDraw(Canvas& canvas) override {
            canvas.fillRect(0, 0, Size.width, Size.height, paint);
            if (!finishedAnimating)
                repaint();
        }

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