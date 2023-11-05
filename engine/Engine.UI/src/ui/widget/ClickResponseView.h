#pragma once

#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/control/ClickableControl.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ClickResponseView:public ClickableControl {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        
        virtual const Ghurund::Core::Type& getTypeImpl() const override { return GET_TYPE(); }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
#pragma endregion

    private:
        inline static const auto DEFAULT_COLOR = ColorValue(0x1f000000);

        uint64_t startTime = 0;
        uint32_t length = 150;
        bool finishedAnimating = true;
        AttrProperty<ColorAttr, Color> color;
        float alpha = 1.0f;

        virtual void onThemeChanged() override;

        virtual void onStateChanged() override;

    public:
        ClickResponseView(const ColorAttr& color = DEFAULT_COLOR):color(color) {}

        inline void setColor(const ColorAttr& color) {
            this->color.set(color);
        }

        __declspec(property(put = setColor)) const ColorAttr& Color;

        virtual void onUpdate(const uint64_t time) override;

        virtual void onDraw(ICanvas& canvas) override;
    };
}