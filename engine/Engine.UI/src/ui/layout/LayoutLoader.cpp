#include "ghuipch.h"
#include "LayoutLoader.h"

#include "core/io/File.h"
#include "ui/control/Clip.h"
#include "ui/control/Border.h"
#include "ui/control/Shadow.h"
#include "ui/control/Space.h"
#include "ui/control/ColorView.h"
#include "ui/control/ImageView.h"
#include "ui/control/InvalidControl.h"
#include "ui/control/PaddingContainer.h"
#include "ui/drawable/BitmapDrawable.h"
#include "ui/drawable/InvalidImageDrawable.h"
#include "ui/drawable/SvgDrawable.h"
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

#include <ranges>

namespace Ghurund::UI {
    LayoutLoader::LayoutLoader(ID2D1Factory6& d2dFactory, Ghurund::Core::ResourceManager& resourceManager)
        :d2dFactory(d2dFactory), resourceManager(resourceManager) {

        registerClass<ClickableControl>();
        registerClass<SelectableView>();
        registerClass<ClickResponseView>();
        registerClass<StateIndicator>();
        registerClass<TextBlock>();
        registerClass<TextView>();
        registerClass<TextField>();
        registerClass<TextBlock>();
        registerClass<ImageView>();
        registerClass<Clip>();
        registerClass<Border>();
        registerClass<Shadow>();
        registerClass<Space>();
        registerClass<ColorView>();

        registerClass<ControlContainer>();
        registerClass<PaddingContainer>();
        registerClass<LinearLayout>();
        registerClass<StackLayout>();
        registerClass<ManualLayout>();
        registerClass<RecyclerView>();

        registerClass<Button>();
        registerClass<CheckBox>();
        registerClass<RadioButton>();
        registerClass<VerticalScrollBar>();
        registerClass<TreeView>();
        registerClass<TabContainer>();
        registerClass<ExpandableContainer>();
    }

    ImageDrawable* LayoutLoader::loadDrawable(const char* str) {
        AString s = str;
        s.replace(L'\\', L'/');
        if (s.startsWith(THEME_IMAGE) && theme) {
            ImageKey imageKey = s.substring(lengthOf(THEME_IMAGE));
            if (theme->Images.containsKey(imageKey))
                return (ImageDrawable*)theme->Images[imageKey]->clone();
        } else {
            FilePath path = convertText<char, wchar_t>(s);
            auto formatSupported = [&path](const ResourceFormat& format) {
                return format.Extension == path.Extension && format.CanLoad;
            };
            if (std::ranges::count_if(Bitmap::FORMATS, formatSupported) == 1) {
                Status result;
                SharedPointer<Bitmap> bitmap = resourceManager.load<Bitmap>(convertText<char, wchar_t>(s), nullptr, &result);
                if (&bitmap == nullptr) {
                    Logger::log(LogType::ERR0R, _T("Failed to load '{}'.\n"), s);
                    return nullptr;
                }
                return ghnew BitmapDrawable(bitmap);
            } else if (std::ranges::count_if(SvgDocument::FORMATS, formatSupported) == 1) {
                Status result;
                SharedPointer<SvgDocument> svg = resourceManager.load<SvgDocument>(convertText<char, wchar_t>(s), nullptr, &result);
                if (&svg == nullptr) {
                    Logger::log(LogType::ERR0R, _T("Failed to load '{}'.\n"), s);
                    return nullptr;
                }
                return ghnew SvgDrawable(svg);
            } else {
                Logger::log(LogType::ERR0R, _T("File format of '{}' is not supported.\n"), s);
            }
        }
        return nullptr;
    }

    Status LayoutLoader::load(Ghurund::Core::ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat* format, LoadOption options) {
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)stream.Data, stream.Size);
        Layout& layout = (Layout&)resource;

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (child && strcmp(child->Value(), "layout") == 0) {
            layout.Controls.addAll(loadControls(*child));
            if (layout.Controls.Empty)
                return Logger::log(LogType::WARNING, Status::FILE_EMPTY, _T("Layout is empty.\n"));
            return Status::OK;
        } else {
            return Logger::log(LogType::ERR0R, Status::INV_FORMAT, _T("Missing 'layout' tag\n"));
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
                    Status result;
                    SharedPointer<Layout> layout = resourceManager.load<Layout>(convertText<char, wchar_t>(s), &Layout::FORMATS[0], &result, LoadOption::DONT_CACHE);
                    if (result == Status::OK) {
                        if (!layout->Controls.Empty) {
                            list.addAll(layout->Controls);
                        } else {
                            Logger::log(LogType::ERR0R, _T("Layout '{}' is empty.\n"), s);
                        }
                    } else {
                        Logger::log(LogType::ERR0R, result, _T("Could not load layout '{}'.\n"), s);
                    }
                } else {
                    Logger::log(LogType::ERR0R, _T("Missing 'layout' attribute.\n"));
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
                Control* control = nullptr;
                AString s = layoutAttr->Value();
                Status result;
                SharedPointer<Layout> layout = resourceManager.load<Layout>(convertText<char, wchar_t>(s), &Layout::FORMATS[0], &result, LoadOption::DONT_CACHE);
                if (result == Status::OK) {
                    if (layout->Controls.Size == 1) {
                        control = layout->Controls[0];
                        control->addReference();
                    } else {
                        Logger::log(LogType::ERR0R, _T("Layout '{}' has to contain exactly one child.\n"), s);
                    }
                } else {
                    Logger::log(LogType::ERR0R, result, _T("Could not load layout '{}'.\n"), s);
                }
                return control;
            }
            Logger::log(LogType::ERR0R, _T("Missing 'layout' attribute.\n"));
            return nullptr;
        } else if (types.containsKey(name)) {
            Control* control = types.get(name)();
            control->load(*this, xml);
            return control;
        }
        Logger::log(LogType::ERR0R, _T("Control type {} not registered in LayoutLoader.\n"), convertText<char, tchar>(AString(name)));
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

    ColorAttr* LayoutLoader::loadColor(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        if (s.startsWith("#")) {
            return ghnew ColorValue(s);
        } else if (s.startsWith(THEME_COLOR) && theme) {
            return ghnew ColorRef(ColorKey(s.substring(lengthOf(THEME_COLOR))));
        }
        return nullptr;
    }

    WString LayoutLoader::loadText(const char* str) {
        return convertText<char, wchar_t>(AString(str));
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
}