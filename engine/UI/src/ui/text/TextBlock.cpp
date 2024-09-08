#include "ghuipch.h"
#include "TextBlock.h"

#include "core/reflection/Property.h"
#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    void TextBlock::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        __super::loadInternal(loader, workingDir, xml);
        auto textFormatAttr = xml.FindAttribute("textFormat");
        if (textFormatAttr) {
            Ghurund::UI::TextFormatRef* format = loader.loadTextFormat(textFormatAttr->Value());
            if (format) {
                TextFormat = format;
                delete format;
            }
		} else {
            Ghurund::UI::TextFormatRef format = Theme::TEXTFORMAT_TEXT_SECONDARY;
            TextFormat = &format;
        }
    }

    /*void TextBlock::onMeasure() {
        const float MAX_LAYOUT_SIZE = 32768.0f;

        if (!Context || !textLayout->Format) {
            //auto text = std::format(_T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
            //Logger::log(LogType::WARNING, text.c_str());
            return;
        }

        /*if (contentSize.width == ContentSize::Width::WRAP) {
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
        }* /
    }*/

    void TextBlock::onDraw(ICanvas& canvas) {
        textLayout.Size = Size;
		textLayout.draw(canvas);
    }

    const Ghurund::Core::Type& TextBlock::GET_TYPE() {
        static auto PROPERTY_TEXT = Property<TextBlock, const TextDocument&>("Text", &getText, (void(TextBlock::*)(const TextDocument&)) &setText);

        static const Ghurund::Core::Type TYPE = TypeBuilder<TextBlock>(NAMESPACE_NAME, GH_STRINGIFY(TextBlock))
            .withZeroArgsConstructor()
            .withProperty(PROPERTY_TEXT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void TextBlock::setTextFormat(Ghurund::UI::TextFormatAttr* textFormat) {
        if (this->textFormat)
            delete this->textFormat;
        if (textFormat) {
            this->textFormat = (Ghurund::UI::TextFormatAttr*)textFormat->clone();
            auto theme = Theme;
            if (theme) {
                textLayout.Format = textFormat->resolve(*theme);
            } else {
                textLayout.Format = nullptr;
			}
        } else {
            this->textFormat = nullptr;
            textLayout.Format = nullptr;
        }
    }

    void TextBlock::dispatchContextChanged() {
        __super::dispatchContextChanged();
        auto theme = Theme;
        if (!theme)
            return;
        if (TextFormat)
            textLayout.Format = TextFormat->resolve(*theme);
        if (Size.Width > 0 && Size.Height > 0)
            textLayout.Size = { Size.Width, Size.Height };
        color.resolve(*theme);
        const UI::Color* c = color.get();
        if (c)
            textLayout.Color = *c;
	}
}