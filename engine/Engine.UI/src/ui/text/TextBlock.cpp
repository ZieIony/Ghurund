#include "ghuipch.h"
#include "TextBlock.h"

#include "ui/Canvas.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/text/TextMetrics.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    void TextBlock::onMeasure(float parentWidth, float parentHeight) {
        textLayout.Size = { parentWidth, parentHeight };
        if (textLayout.buildLayout(Context->DWriteFactory) != Status::OK) {
            Logger::log(LogType::WARNING, _T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
            __super::onMeasure(parentWidth, parentHeight);
            return;
        }

        TextMetrics textMetrics = textLayout.TextMetrics;

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = std::max(minSize.width, std::ceil(textMetrics.width));
        } else {
            if (preferredSize.width == PreferredSize::Width::FILL) {
                measuredSize.width = std::max(minSize.width, parentWidth);
            } else {
                measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
            }
            textLayout.Size = { measuredSize.width, parentHeight };
            if (textLayout.buildLayout(Context->DWriteFactory) != Status::OK) {
                Logger::log(LogType::WARNING, _T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
                __super::onMeasure(parentWidth, parentHeight);
                return;
            }
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
        textLayout.Color = color->getValue(*this);
        textLayout.draw(canvas, 0, 0);
    }

    const Ghurund::Core::Type& TextBlock::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<TextBlock>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextBlock>(NAMESPACE_NAME, GH_STRINGIFY(TextBlock))
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
        if (Size.width > 0 && Size.height > 0)
            textLayout.Size = { Size.width, Size.height };
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
            TextColor = *loader.loadColor(textColorAttr->Value());
        auto textFormatAttr = xml.FindAttribute("textFormat");
        if (textFormatAttr) {
            Ghurund::UI::TextFormat* format = loader.loadTextFormat(textFormatAttr->Value());
            TextFormat = format;
            format->release();
        }
        return Status::OK;
    }
}