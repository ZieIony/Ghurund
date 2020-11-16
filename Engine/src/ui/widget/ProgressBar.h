#pragma once

#include "ui/Style.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    class ProgressBar:public Control {
    private:
        float progress = 0.0f;
        bool indeterminate = false;
        unsigned int progressColor = 0xffff0000, backgroundColor = 0xff00ff00;
        Paint paint;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ProgressBar>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ProgressBar))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class Theme;

    class ProgressBarStyle:public Ghurund::UI::Style<ProgressBar> {
    public:
        ProgressBarStyle(Theme& theme);

        virtual void apply(ProgressBar& progressBar) const override;

        virtual void onStateChanged(ProgressBar& progressBar) const override;
    };
}