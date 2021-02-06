#include "TextBlock.h"
#include "ui/style/Theme.h"
#include "ui/LayoutLoader.h"
#include "core/logging/Logger.h"

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
        } else {
            if (preferredSize.width == PreferredSize::Width::FILL) {
                measuredSize.width = std::max(minSize.width, parentWidth);
            } else {
                measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
            }
            textLayout->Release();
            makeLayout(measuredSize.width, parentHeight);
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = std::max(minSize.height, std::ceil(textMetrics.height));
        } else  if (preferredSize.height == PreferredSize::Height::FILL) {
            measuredSize.height = std::max(minSize.height, parentHeight);
        } else {
            measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
        }
    }

    void TextBlock::onDraw(Canvas& canvas) {
        paint.Color = TextColor;
        if (textLayout)
            canvas.drawText(textLayout, 0, 0, paint);
    }

    void TextBlock::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (!Theme)
            return;
        if (!TextStyle)
            TextStyle = Theme->TextStyles[Theme::TEXTSTYLE_TEXT_PRIMARY];
        if (!TextColor)
            TextColor = Theme->ColorForegroundPrimaryOnBackground;
        if (!textLayout && Size.width > 0 && Size.height > 0)
            makeLayout(Size.width, Size.height);
    }

    Status TextBlock::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto textAttr = xml.FindAttribute("text");
        if (textAttr) {
            Text = loader.loadText(textAttr->Value());
        }
        auto textColorAttr = xml.FindAttribute("textColor");
        if (textColorAttr)
            TextColor = loader.loadColor(textColorAttr->Value());
        auto textStyleAttr = xml.FindAttribute("textStyle");
        if (textStyleAttr) {
            Ghurund::UI::TextStyle* style = loader.loadFont(textStyleAttr->Value());
            TextStyle = style;
            style->release();
        }
        return Status::OK;
    }
}