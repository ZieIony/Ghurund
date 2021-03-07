#include "ghpch.h"
#include "TextBlock.h"

#include "ui/Canvas.h"
#include "ui/LayoutLoader.h"
#include "ui/style/Theme.h"

namespace Ghurund::UI {
    void TextBlock::makeLayout(float width, float height) {
        Context->Graphics.DWriteFactory->CreateTextLayout(
            text.Data,
            (UINT32)text.Size,
            TextFormat->Format,
            width,
            height,
            &textLayout
        );
    }

    void TextBlock::onMeasure(float parentWidth, float parentHeight) {
        if (!textFormat) {
            Logger::log(LogType::WARNING, "TextBlock ({}) was not measured, because its textFormat is null\n", text);
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
        if (textLayout)
            canvas.drawText(textLayout, 0, 0, textColor);
    }

    const Ghurund::Type& TextBlock::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<TextBlock>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(TextBlock))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void TextBlock::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (!Theme)
            return;
        if (!TextFormat)
            TextFormat = Theme->TextFormats[Theme::TEXTFORMAT_TEXT_PRIMARY];
        if (!TextColor)
            TextColor = Theme->Colors[Theme::COLOR_PRIMARY_ONBACKGROUND];
        if (!textLayout && Size.width > 0 && Size.height > 0)
            makeLayout(Size.width, Size.height);
    }

    Status TextBlock::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto textAttr = xml.FindAttribute("text");
        if (textAttr)
            Text = loader.loadText(textAttr->Value());
        auto textColorAttr = xml.FindAttribute("textColor");
        if (textColorAttr)
            TextColor = loader.loadColor(textColorAttr->Value());
        auto textFormatAttr = xml.FindAttribute("textFormat");
        if (textFormatAttr) {
            Ghurund::UI::TextFormat* format = loader.loadTextFormat(textFormatAttr->Value());
            TextFormat = format;
            format->release();
        }
        return Status::OK;
    }
}