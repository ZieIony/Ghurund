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
#include "ui/layout/ManualLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/style/Theme.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/StateIndicator.h"
#include "ui/widget/VerticalScrollBar.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/button/CheckBox.h"
#include "ui/widget/button/RadioButton.h"
#include "ui/widget/text/TextView.h"
#include "ui/widget/text/TextField.h"
#include "ui/widget/tree/TreeView.h"
#include "core/string/TextConversionUtils.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI {
    LayoutLoader::LayoutLoader() {
        workingDir.push(DirectoryPath(L"."));
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

        registerClass(Button::TYPE);
        registerClass(CheckBox::TYPE);
        registerClass(RadioButton::TYPE);
        registerClass(VerticalScrollBar::TYPE);
        registerClass(TreeView::TYPE);
    }

    Status LayoutLoader::load(const Buffer& data, PointerList<Control*>& output) {
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)data.Data, data.Size);

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (child && strcmp(child->Value(), "layout") == 0) {
            output.addAll(loadControls(*child));
            return Status::OK;
        } else {
            return Logger::log(LogType::ERR0R, Status::INV_FORMAT, _T("missing 'layout' tag\n"));
        }
    }

    Status LayoutLoader::load(const FilePath& path, PointerList<Control*>& output) {
        File file(path);
        if (!file.Exists)
            return Status::FILE_DOESNT_EXIST;
        Status result = file.read();
        if (result == Status::OK) {
            workingDir.push(path.Directory);
            result = load(Buffer(file.Data, file.Size), output);
            workingDir.pop();
        }
        return result;
    }

    PointerList<Control*> LayoutLoader::loadControls(const tinyxml2::XMLElement& xml) {
        PointerList<Control*> list;
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            if (strcmp(child->Value(), "include") == 0) {
                auto layoutAttr = child->FindAttribute("layout");
                if (layoutAttr) {
                    WString s = toWideChar(AString(layoutAttr->Value()));
                    if (s.startsWith(FILE_PROTOCOL)) {
                        PointerList<Control*> controls;
                        Status result = load(getPath(s), controls);
                        if (result == Status::OK)
                            list.addAll(controls);
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
                WString s = toWideChar(AString(layoutAttr->Value()));
                if (s.startsWith(FILE_PROTOCOL)) {
                    PointerList<Control*> controls;
                    Status result = load(getPath(s), controls);
                    if (result == Status::OK && !controls.Empty) {
                        Control* control = controls[0];
                        control->addReference();
                        return control;
                    }
                }
            }
        } else if (types.contains(name)) {
            Type* type = types.get(name);
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
            return ghnew Rect(context->Graphics2D);
        } else if (s.startsWith("roundRect")) {
            float radius = (float)atof(s.substring(s.find(",") + 1).trim().Data);
            return ghnew RoundRect(context->Graphics2D, radius);
        }
        return nullptr;
    }

    uint32_t LayoutLoader::loadColor(const char* str) {
        WString s = toWideChar(AString(str));
        uint32_t value = 0;
        const wchar_t* themeProtocol = L"theme://color/";
        if (s.startsWith(L"#")) {
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
        } else if (s.startsWith(themeProtocol) && theme) {
            WString colorKey = s.substring(lengthOf(themeProtocol));
            if (theme->Colors.contains(colorKey))
                return theme->Colors[colorKey];
        }
        return value;
    }

    BitmapImage* LayoutLoader::loadImage(const char* str) {
        WString s = toWideChar(AString(str));
        const wchar_t* themeProtocol = L"theme://image/";
        if (s.startsWith(FILE_PROTOCOL)) {
            return BitmapImage::makeFromImage(*context, getPath(s));
        } else if (s.startsWith(themeProtocol) && theme) {
            WString imageKey = s.substring(lengthOf(themeProtocol));
            if (theme->Images.contains(imageKey)) {
                BitmapImage* image = theme->Images[imageKey];
                image->addReference();
                return image;
            }
        }
        return nullptr;
    }

    WString LayoutLoader::loadText(const char* str) {
        return toWideChar(AString(str));
    }

    TextFormat* LayoutLoader::loadTextFormat(const char* str) {
        WString s = toWideChar(AString(str));
        const wchar_t* themeProtocol = L"theme://textFormat/";
        if (s.startsWith(FILE_PROTOCOL)) {
            //auto textFormat = ghnew TextFormat()
        } else if (s.startsWith(themeProtocol) && theme) {
            WString fontKey = s.substring(lengthOf(themeProtocol));
            if (theme->TextFormats.contains(fontKey)) {
                TextFormat* style = theme->TextFormats[fontKey];
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

    WString LayoutLoader::getPath(const WString& path) {
        WStringView sView = WStringView(path).substring(lengthOf(FILE_PROTOCOL));
        if (sView.startsWith(L"~/"))
            return FilePath(sView.substring(lengthOf(L"~/")));
        auto fileName = fmt::format(L"{}/{}", WorkingDirectory.toString().Data, sView);
        return WString(fileName.c_str());
    }
}