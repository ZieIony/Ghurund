#pragma once

#include "ui/control/Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ProgressBar:public Control {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ProgressBar::GET_TYPE();
#pragma endregion

    private:
        float progress = 0.0f;
        bool indeterminate = false;
        AttrProperty<ColorAttr, Color> progressColor;
        AttrProperty<ColorAttr, Color> backgroundColor;

    protected:
        virtual void onThemeChanged() override;

        virtual void onStateChanged() override;

        virtual void onDraw(ICanvas& canvas) override;

    public:
        ProgressBar(
            const ColorAttr& progressColor = ColorRef(Theme::COLOR_ACCENT),
            const ColorAttr& backgroundColor = ColorRef(Theme::COLOR_CONTROL))
            :progressColor(progressColor), backgroundColor(backgroundColor)
        {}

        inline float getProgress() const {
            return progress;
        }

        inline void setProgress(float progress) {
            this->progress = std::max(0.0f, std::min(progress, 1.0f));
            indeterminate = false;
        }

        __declspec(property(get = getProgress, put = setProgress)) float Progress;

        inline bool isIndeterminate() const {
            return indeterminate;
        }

        inline void setIndeterminate(bool indeterminate) {
            this->indeterminate = indeterminate;
        }

        __declspec(property(get = isIndeterminate, put = setIndeterminate)) bool Indeterminate;

        inline void setBackgroundColor(const ColorAttr& color) {
            backgroundColor.set(color);
        }

        __declspec(property(put = setBackgroundColor)) const ColorAttr& BackgroundColor;

        inline void setProgressColor(const ColorAttr& color) {
            progressColor.set(color);
        }

        __declspec(property(put = setProgressColor)) const ColorAttr& ProgressColor;
    };
}