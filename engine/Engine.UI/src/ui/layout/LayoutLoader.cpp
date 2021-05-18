#include "ghuipch.h"
#include "LayoutLoader.h"

#include "core/io/File.h"
#include "ui/control/Clip.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Space.h"
#include "ui/control/ColorView.h"
#include "ui/control/ImageView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/ManualLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/style/Theme.h"
#include "ui/text/TextBlock.h"
#include "ui/text/TextField.h"
#include "ui/text/TextView.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/ExpandableContainer.h"
#include "ui/widget/StateIndicator.h"
#include "ui/widget/VerticalScrollBar.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/tree/TreeView.h"
#include "ui/widget/tab/TabContainer.h"
#include "core/string/TextConversionUtils.h"
#include "core/logging/Formatter.h"

namespace Ghurund::UI {
    LayoutLoader::LayoutLoader(ID2D1Factory6& d2dFactory, Ghurund::ResourceManager& resourceManager)
        :d2dFactory(d2dFactory), resourceManager(resourceManager) {

        registerClass(ClickableControl::TYPE);
        registerClass(SelectableView::TYPE);
        registerClass(ClickResponseView::TYPE);
        registerClass(StateIndicator::TYPE);
        registerClass(TextBlock::TYPE);
        registerClass(TextView::TYPE);
        registerClass(TextField::TYPE);
        registerClass(TextBlock::TYPE);
        registerClass(ImageView::TYPE);
        registerClass(Clip::TYPE);
        registerClass(Border::TYPE);
        registerClass(Shadow::TYPE);
        registerClass(Space::TYPE);
        registerClass(ColorView::TYPE);

        registerClass(ControlContainer::TYPE);
        registerClass(PaddingContainer::TYPE);
        registerClass(LinearLayout::TYPE);
        registerClass(StackLayout::TYPE);
        registerClass(ManualLayout::TYPE);
        registerClass(RecyclerView::TYPE);

        registerClass(Button::TYPE);
        registerClass(CheckBox::TYPE);
        registerClass(RadioButton::TYPE);
        registerClass(VerticalScrollBar::TYPE);
        registerClass(TreeView::TYPE);
        registerClass(TabContainer::TYPE);
        registerClass(ExpandableContainer::TYPE);
    }

    ImageDrawable* LayoutLoader::loadDrawable(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        if (s.startsWith(FILE_PROTOCOL)) {
            return nullptr;// resourceLoader->loadDrawable(getPath(str));
        } else if (s.startsWith(THEME_IMAGE) && theme) {
            ImageKey imageKey = s.substring(lengthOf(THEME_IMAGE));
            if (theme->Images.containsKey(imageKey))
                return (ImageDrawable*)theme->Images[imageKey]->clone();
        }
        return nullptr;
    }

    Status LayoutLoader::load(Ghurund::ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat * format, LoadOption options) {
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)stream.Data, stream.Size);
        Layout& layout = (Layout&)resource;

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (child && strcmp(child->Value(), "layout") == 0) {
            layout.Controls.addAll(loadControls(*child));
            return Status::OK;
        } else {
            return Logger::log(LogType::ERR0R, Status::INV_FORMAT, _T("missing 'layout' tag\n"));
        }
    }

    PointerList<Control*> LayoutLoader::loadControls(const tinyxml2::XMLElement& xml) {
        PointerList<Control*> list;
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            if (strcmp(child->Value(), "include") == 0) {
                auto layoutAttr = child->FindAttribute("layout");
                if (layoutAttr) {
                    AString s = layoutAttr->Value();
                    s.replace('\\', '/');
                    if (s.startsWith(FILE_PROTOCOL)) {
                        SharedPointer<Layout> layout = resourceManager.load<Layout>(getPath(s));
                        list.addAll(layout->Controls);
                    }
                }
            } else {
                Control* control = loadControl(*child);
                if (control) {
                    list.add(control);
                    control->release();
                }
            }
            child = child->NextSiblingElement();
        }
        return list;
    }

    Control* LayoutLoader::loadControl(const tinyxml2::XMLElement& xml) {
        const char* name = xml.Value();
        if (strcmp(name, "include") == 0) {
            auto layoutAttr = xml.FindAttribute("layout");
            if (layoutAttr) {
                AString s = layoutAttr->Value();
                s.replace('\\', '/');
                if (s.startsWith(FILE_PROTOCOL)) {
                    SharedPointer<Layout> layout = resourceManager.load<Layout>(getPath(s));
                    if (!layout->Controls.Empty) {
                        Control* control = layout->Controls[0];
                        control->addReference();
                        return control;
                    }
                }
            }
        } else if (types.containsKey(name)) {
            const Type* type = types.get(name);
            Control* control = (Control*)type->Constructor->newInstance();
            control->load(*this, xml);
            return control;
        }
        Logger::log(LogType::ERR0R, _T("Control type {} not registered in LayoutLoader.\n"), String(name));
        return nullptr;
    }

    Shape* LayoutLoader::loadShape(const char* str) {
        AString s = str;
        if (s == "rect") {
            return ghnew Rect(d2dFactory);
        } else if (s.startsWith("roundRect")) {
            float radius = (float)atof(s.substring(s.find(",") + 1).trim().Data);
            return ghnew RoundRect(d2dFactory, radius);
        }
        return nullptr;
    }

    uint32_t LayoutLoader::loadColor(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        uint32_t value = 0;
        if (s.startsWith("#")) {
            s = s.toLowerCase();
            for (size_t i = 1; i < s.Length; i++) {
                if (s[i] >= '0' && s[i] <= '9') {
                    value = value * 16 + (s[i] - '0');
                } else if (s[i] >= 'a' && s[i] <= 'f') {
                    value = value * 16 + (s[i] - 'a' + 10);
                } else {
                    return 0;
                }
            }
        } else if (s.startsWith(THEME_COLOR) && theme) {
            ColorKey colorKey = s.substring(lengthOf(THEME_COLOR));
            if (theme->Colors.containsKey(colorKey))
                return theme->Colors[colorKey];
        }
        return value;
    }

    WString LayoutLoader::loadText(const char* str) {
        return toWideChar(AString(str));
    }

    TextFormat* LayoutLoader::loadTextFormat(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        if (s.startsWith(FILE_PROTOCOL)) {
            //auto textFormat = ghnew TextFormat()
        } else if (s.startsWith(THEME_TEXTFORMAT) && theme) {
            TextFormatKey textFormatKey = s.substring(lengthOf(THEME_TEXTFORMAT));
            if (theme->TextFormats.containsKey(textFormatKey)) {
                TextFormat* style = theme->TextFormats[textFormatKey];
                style->addReference();
                return style;
            }
        }
        return nullptr;
    }

    Status LayoutLoader::loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment) {
        auto alignmentParam = xml.FindAttribute("alignment");
        if (alignmentParam) {
            AStringView alignmentStr = alignmentParam->Value();
            size_t comma = alignmentStr.find(",");
            if (comma == alignmentStr.Size)
                return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("Invalid parameter value: {}\n"), alignmentStr);
            AStringView horizontal = alignmentStr.substring(0, comma).trim();
            if (horizontal == "left") {
                (*alignment).horizontal = Alignment::Horizontal::LEFT;
            } else if (horizontal == "center") {
                (*alignment).horizontal = Alignment::Horizontal::CENTER;
            } else if (horizontal == "right") {
                (*alignment).horizontal = Alignment::Horizontal::RIGHT;
            } else {
                return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("Invalid parameter value: {}\n"), alignmentStr);
            }
            AStringView vertical = alignmentStr.substring(comma + 1, alignmentStr.Length - comma - 1).trim();
            if (vertical == "top") {
                (*alignment).vertical = Alignment::Vertical::TOP;
            } else if (vertical == "center") {
                (*alignment).vertical = Alignment::Vertical::CENTER;
            } else if (vertical == "bottom") {
                (*alignment).vertical = Alignment::Vertical::BOTTOM;
            } else {
                return Logger::log(LogType::ERR0R, Status::INV_PARAM, _T("Invalid parameter value: {}\n"), alignmentStr);
            }
        }

        return Status::OK;
    }

    WString LayoutLoader::getPath(const AString& path) {
        AStringView sView = AStringView(path);
        if (sView.startsWith(FILE_PROTOCOL))
            sView = sView.substring(lengthOf(FILE_PROTOCOL));
        return toWideChar(AString(sView.Data));
    }
}