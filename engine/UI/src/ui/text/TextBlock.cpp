#include "ghuipch.h"
#include "TextBlock.h"

#include "core/reflection/Property.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    void TextBlock::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        __super::loadInternal(loader, workingDir, xml);
        auto textFormatAttr = xml.FindAttribute("font");
        if (textFormatAttr) {
            Ghurund::UI::FontRef* format = loader.loadFont(textFormatAttr->Value());
            if (format) {
                Font = format;
                delete format;
            }
		} else {
            Ghurund::UI::FontRef format = Theme::FONT_TEXT_SECONDARY;
            Font = &format;
        }
    }

    /*void TextBlock::onMeasure() {
        const float MAX_LAYOUT_SIZE = 32768.0f;

        if (!Context || !textLayout->Format) {
            //auto typeName = std::format(_T("TextBlock ({}) was not measured, because its textLayout is invalid\n"), Text);
            //Logger::log(LogType::WARNING, typeName.c_str());
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

    void TextBlock::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		textLayout.draw(group);
    }

    const Ghurund::Core::Type& TextBlock::GET_TYPE() {
        static auto PROPERTY_TEXT = Property<TextBlock, TextDocument*>("Document", &getDocument, &setDocument);

        static const Ghurund::Core::Type TYPE = TypeBuilder<TextBlock>()
            .withProperty(PROPERTY_TEXT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void TextBlock::setFont(Ghurund::UI::FontAttr* font) {
        if (this->font)
            delete this->font;
        if (font) {
            this->font = (Ghurund::UI::FontAttr*)font->clone();
            auto theme = Theme;
            if (theme) {
                textLayout.Document->Font = font->resolve(*theme);
            } else {
                //textLayout.Document->Font = nullptr;
			}
        } else {
            this->font = nullptr;
            //textLayout.Document->Font = nullptr;
        }
    }

    void TextBlock::dispatchContextChanged() {
        __super::dispatchContextChanged();
        auto theme = Theme;
        if (!theme)
            return;
        //if (Font)
            //textLayout.Document->Font = Font->resolve(*theme);
        //if (Size.Width > 0 && Size.Height > 0)
          //  textLayout.Size = { Size.Width, Size.Height };
        color.resolve(*theme);
        const UI::Color* c = color.get();
        //if (c)
            //textLayout.Document->TextColor = *c;
	}
}