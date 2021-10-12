#pragma once

#include "ui/control/Control.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/Style.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ProgressBar:public Control {
    private:
        float progress = 0.0f;
        bool indeterminate = false;
        ColorAttr* progressColor = nullptr;
        ColorAttr* backgroundColor = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ProgressBar(
            const ColorAttr& progressColor = ColorRef(Theme::COLOR_ACCENT),
            const ColorAttr& backgroundColor = ColorRef(Theme::COLOR_CONTROL))
        {
            PreferredSize.width = PreferredSize::Width::FILL;
            PreferredSize.height = 4;
        }

        ~ProgressBar() {
            delete progressColor;
            delete backgroundColor;
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

        inline const ColorAttr& getBackgroundColor() const {
            return *backgroundColor;
        }

        inline void setBackgroundColor(const ColorAttr& color) {
            delete backgroundColor;
            backgroundColor = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getBackgroundColor, put = setBackgroundColor)) const ColorAttr& BackgroundColor;

        inline const ColorAttr& getProgressColor() const {
            return *progressColor;
        }

        inline void setProgressColor(const ColorAttr& color) {
            delete progressColor;
            progressColor = (ColorAttr*)color.clone();
        }

        __declspec(property(get = getProgressColor, put = setProgressColor)) const ColorAttr& ProgressColor;

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class ProgressBarStyle:public TypedStyle<ProgressBar> {
    public:
        virtual void onStateChanged(ProgressBar& control) const override;
    };
}