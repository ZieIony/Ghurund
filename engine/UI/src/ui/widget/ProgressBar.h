#pragma once

#include "ui/control/Control.h"
#include "ui/theme/Theme.h"
#include "ui/theme/ThemedValueProperty.h"

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
        ThemedValueProperty<ColorKey, Color> progressColor;
        ThemedValueProperty<ColorKey, Color> backgroundColor;

        inline void setBackgroundColor(const ThemedColor& color) {
            if (color.Key) {
                setBackgroundColor(*color.Key);
            } else {
                setBackgroundColor(color.Value);
            }
        }

        inline void setProgressColor(const ThemedColor& color) {
            if (color.Key) {
                setProgressColor(*color.Key);
            } else {
                setProgressColor(color.Value);
            }
        }

    protected:
        virtual void onThemeChanged() override;

        virtual void onStateChanged() override;

        virtual void onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) override;

    public:
        ProgressBar(
            const ThemedColor& progressColor = Theme::COLOR_ACCENT,
            const ThemedColor& backgroundColor = Theme::COLOR_CONTROL)
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

        inline void setBackgroundColor(const Color& color) {
            backgroundColor.set(color);
        }

        inline void setBackgroundColor(const ColorKey& color) {
            backgroundColor.set(color);
        }

        __declspec(property(put = setBackgroundColor)) const Color& BackgroundColor;

        inline void setProgressColor(const Color& color) {
            progressColor.set(color);
        }

        inline void setProgressColor(const ColorKey& color) {
            progressColor.set(color);
        }

        __declspec(property(put = setProgressColor)) const Color& ProgressColor;
    };
}