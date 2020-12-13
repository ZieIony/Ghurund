#include "TextBlock.h"
#include "ui/Theme.h"

namespace Ghurund::UI {
    void TextBlock::onMeasure(float parentWidth, float parentHeight) {
        if (!font) {
            Logger::log(LogType::WARNING, "TextBlock ({}) was not measured, because its font is null\n", text);
            __super::onMeasure(parentWidth, parentHeight);
            return;
        }

        if (!textLayout)
            makeLayout(parentWidth, parentHeight);

        DWRITE_TEXT_METRICS textMetrics;
        textLayout->GetMetrics(&textMetrics);

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::max(minSize.width, std::ceil(textMetrics.width));
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
            textLayout->Release();
            makeLayout(measuredSize.width, parentHeight);
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = std::max(minSize.height, std::ceil(textMetrics.height));
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
        }
    }

    void TextBlock::onDraw(Canvas& canvas) {
        paint.Color = TextColor;
        canvas.drawText(textLayout, 0, 0, paint);
    }

    void TextBlock::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (!Theme)
            return;
        if (!Font)
            Font = Theme->PrimaryTextFont;
        if (!TextColor)
            TextColor = Theme->ColorForegroundPrimaryOnBackground;
        if (!textLayout && Size.width > 0 && Size.height > 0)
            makeLayout(Size.width, Size.height);
    }
}