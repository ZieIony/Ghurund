#pragma once

#include "ui/Style.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    class ProgressBar:public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ProgressBar);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ProgressBar>();

        float progress = 0.0f;
        bool indeterminate = false;
        unsigned int progressColor, backgroundColor;
        Paint paint;

    public:
        ProgressBar() {
            PreferredSize.width = PreferredSize::Width::FILL;
            PreferredSize.height = 4;
        }

        ProgressBar(Style<ProgressBar>& style);

        inline float getProgress() const {
            return progress;
        }

        inline void setProgress(float progress) {
            this->progress = std::max(0.0f, std::min(progress, 1.0f));
        }

        __declspec(property(get = getProgress, put = setProgress)) float Progress;

        inline bool isIndeterminate() const {
            return indeterminate;
        }

        inline void setIndeterminate(bool indeterminate) {
            this->indeterminate = indeterminate;
        }

        __declspec(property(get = isIndeterminate, put = setIndeterminate)) bool Indeterminate;

        inline unsigned int getBackgroundColor() const {
            return backgroundColor;
        }

        inline void setBackgroundColor(unsigned int color) {
            backgroundColor = color;
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) unsigned int BackgroundColor;

        inline unsigned int getProgressColor() const {
            return progressColor;
        }

        inline void setProgressColor(unsigned int color) {
            progressColor = color;
        }

        __declspec(property(get = getProgressColor, put = setProgressColor)) unsigned int ProgressColor;

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<ProgressBar>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE());

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class Theme;

    class ProgressBarStyle:public Ghurund::UI::Style<ProgressBar> {
    public:
        ProgressBarStyle(Theme& theme);

        virtual void onStateChanged(ProgressBar& progressBar) const override;
    };
}