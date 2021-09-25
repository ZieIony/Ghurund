#pragma once

#include "ui/Color.h"
#include "ui/style/Style.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ProgressBar:public Control {
    private:
        float progress = 0.0f;
        bool indeterminate = false;
        Color progressColor = 0xffff0000, backgroundColor = 0xff00ff00;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ProgressBar() {
            PreferredSize.width = PreferredSize::Width::FILL;
            PreferredSize.height = 4;
        }

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

        inline const Color& getBackgroundColor() const {
            return backgroundColor;
        }

        inline void setBackgroundColor(const Color& color) {
            backgroundColor = color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) const Color& BackgroundColor;

        inline const Color& getProgressColor() const {
            return progressColor;
        }

        inline void setProgressColor(const Color& color) {
            progressColor = color;
        }

        __declspec(property(get = getProgressColor, put = setProgressColor)) const Color& ProgressColor;

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class Theme;

    class ProgressBarStyle:public Ghurund::UI::Style {
    public:
        virtual void onThemeChanged(Control& control) const override;

        virtual void onStateChanged(Control& control) const override;
    };
}