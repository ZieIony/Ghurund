#include "LayoutLoader.h"

#include "ui/control/Clip.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Space.h"
#include "ui/control/ColorView.h"
#include "ui/control/ImageView.h"
#include "ui/control/TextBlock.h"
#include "ui/control/PaddingContainer.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/style/Theme.h"
#include "core/string/TextConversionUtils.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI {
    LayoutLoader::LayoutLoader() {
        registerClass(PaddingContainer::TYPE);
        registerClass(LinearLayout::TYPE);
        registerClass(TextBlock::TYPE);
        registerClass(ImageView::TYPE);
        registerClass(StackLayout::TYPE);
        registerClass(Clip::TYPE);
        registerClass(Border::TYPE);
        registerClass(Shadow::TYPE);
        registerClass(Space::TYPE);
        registerClass(ColorView::TYPE);
    }

    PointerList<Control*> LayoutLoader::load(ResourceContext& context, const Buffer& data) {
        PointerList<Control*> list;
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)data.Data, data.Size);

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (child && strcmp(child->Value(), "layout") == 0)
            list.addAll(loadControls(context, *child));
        return list;
    }

    PointerList<Control*> LayoutLoader::loadControls(ResourceContext& context, const tinyxml2::XMLElement& xml) {
        PointerList<Control*> list;
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            Control* control = loadControl(context, *child);
            if (control) {
                list.add(control);
                control->release();
            }
            child = child->NextSiblingElement();
        }
        return list;
    }

    Control* LayoutLoader::loadControl(ResourceContext& context, const tinyxml2::XMLElement& xml) {
        const char* name = xml.Value();
        if (types.contains(name)) {
            Type* type = types.get(name);
            Control* control = (Control*)type->Constructor->newInstance();
            control->load(*this, context, xml);
            return control;
        }
        Logger::log(LogType::ERR0R, _T("Control type {} not registered in LayoutLoader.\n"), String(name));
        return nullptr;
    }

    Shape* LayoutLoader::loadShape(ResourceContext& context, const char* str) {
        AString s = str;
        if (s == "rect") {
            return ghnew Rect(context.Graphics2D);
        } else if (s.startsWith("roundRect")) {
            float radius = (float)atof(s.substring(s.find(",") + 1).trim().Data);
            return ghnew RoundRect(context.Graphics2D, radius);
        }
        return nullptr;
    }

    uint32_t LayoutLoader::loadColor(const char* str) {
        AString s = str;
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
        }
        return value;
    }

    WString LayoutLoader::loadText(const char* str) {
        return toWideChar(AString(str));
    }

    TextStyle* LayoutLoader::loadFont(ResourceContext& context, const char* str) {
        WString s = toWideChar(AString(str));
        const wchar_t* fileProtocol = L"file://";
        const wchar_t* themeProtocol = L"theme://";
        if (s.startsWith(fileProtocol)) {
            auto filePath = FilePath(s.substring(lengthOf(fileProtocol)));
            //auto font = ghnew TextStyle()
        } else if (s.startsWith(themeProtocol) && theme) {
            WString fontKey = s.substring(lengthOf(themeProtocol));
            if (theme->TextStyles.contains(fontKey))
                return theme->TextStyles[fontKey];
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
}