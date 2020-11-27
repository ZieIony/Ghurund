#include "TextBlock.h"

namespace Ghurund::UI {
    void TextBlock::onMeasure(float parentWidth, float parentHeight) {
        if (!font) {
            Logger::log(LogType::WARNING, "TextBlock ({}) was not measured, because its font is null\n", text);
            __super::onMeasure(parentWidth, parentHeight);
            return;
        }

        if (textLayout.Get() == nullptr)
            textLayout = font->makeLayout(text, parentWidth, parentHeight);

        DWRITE_TEXT_METRICS textMetrics;
        textLayout->GetMetrics(&textMetrics);

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::max(minSize.width, std::ceil(textMetrics.width));
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = std::max(minSize.height, std::ceil(textMetrics.height));
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
        }
    }

    void TextBlock::onDraw(Canvas& canvas) {
        if (textLayout.Get())
            canvas.drawText(textLayout.Get(), 0, 0, paint);
    }
}