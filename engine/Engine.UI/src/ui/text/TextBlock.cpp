#include "ghuipch.h"
#include "TextBlock.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/text/TextMetrics.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    void TextBlock::onMeasure(float parentWidth, float parentHeight) {
        const float MAX_LAYOUT_SIZE = 32768.0f;

        if (!Context || !textLayout->Format) {
            auto text = std::format(_T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
            Logger::log(LogType::WARNING, text.c_str());
            return;
        }

        /*if (preferredSize.width == PreferredSize::Width::WRAP) {
            textLayout->Size = { MAX_LAYOUT_SIZE, MAX_LAYOUT_SIZE };
            if (textLayout->refresh() != Status::OK) {
                Logger::log(LogType::WARNING, _T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
                return;
            }
            TextMetrics textMetrics = textLayout->TextMetrics;
            measuredSize.Width = std::max(minSize.width.resolve(parentWidth), std::ceil(textMetrics.width));
            measuredSize.Height = resolveHeight(std::ceil(textMetrics.height), parentWidth, parentHeight);
        } else {
            measuredSize.Width = resolveWidth(0, parentWidth, parentHeight);
            textLayout->Size = { measuredSize.Width, MAX_LAYOUT_SIZE };
            if (textLayout->refresh() != Status::OK) {
                Logger::log(LogType::WARNING, _T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
                return;
            }
            TextMetrics textMetrics = textLayout->TextMetrics;
            measuredSize.Height = resolveHeight(std::ceil(textMetrics.height), parentWidth, parentHeight);
        }*/
    }

    void TextBlock::onDraw(ICanvas& canvas) {
        textLayout->Color = color->getValue(*this);
        canvas.drawText(*textLayout, 0, 0);
    }

    const Ghurund::Core::Type& TextBlock::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextBlock>(NAMESPACE_NAME, GH_STRINGIFY(TextBlock))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void TextBlock::dispatchContextChanged() {
        __super::dispatchContextChanged();
        if (!Theme)
            return;
        if (!TextFormat)
            TextFormat = Theme->TextFormats[Theme::TEXTFORMAT_TEXT_PRIMARY].get();
        if (Size.Width > 0 && Size.Height > 0)
            textLayout->Size = { Size.Width, Size.Height };
    }

    void TextBlock::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto textAttr = xml.FindAttribute("text");
        if (textAttr)
            Text = loader.loadText(textAttr->Value());
        auto textColorAttr = xml.FindAttribute("textColor");
        if (textColorAttr)
            TextColor = *loader.loadColor(textColorAttr->Value());
        auto textFormatAttr = xml.FindAttribute("textFormat");
        if (textFormatAttr) {
            Ghurund::UI::TextFormat* format = loader.loadTextFormat(textFormatAttr->Value());
            TextFormat = format;
            format->release();
        }
    }
}