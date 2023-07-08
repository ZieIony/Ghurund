#pragma once

#include "ui/control/Control.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/Style.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ProgressBar:public Control {
    private:
        float progress = 0.0f;
        bool indeterminate = false;
        AttrProperty<ColorAttr, Color> progressColor;
        AttrProperty<ColorAttr, Color> backgroundColor;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

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

        virtual void onThemeChanged() override;

        virtual void onDraw(ICanvas& canvas) override;

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    class ProgressBarStyle:public TypedStyle<ProgressBar> {
    public:
        virtual void onStateChanged(ProgressBar& control) const override;
    };
}