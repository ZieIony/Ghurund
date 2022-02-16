#pragma once

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
        ColorAttr* color = nullptr;
        float alpha = 1.0f;

    public:
        ClickResponseView(const ColorAttr& color = DEFAULT_COLOR) {
            Color = color;
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }

        ~ClickResponseView() {
            delete color;
        }

        inline const ColorAttr& getColor() const {
            return *color;
        }

        inline void setColor(const ColorAttr& color) {
            delete this->color;
            this->color = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getColor, put = setColor)) const ColorAttr& Color;

        virtual void onUpdate(const uint64_t time) override;

        virtual void onDraw(ICanvas& canvas) override;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;
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