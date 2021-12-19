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
#include "ui/drawable/InvalidImageDrawable.h"
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
    LayoutLoader::LayoutLoader(
        Ghurund::Core::ResourceManager& resourceManager,
        ShapeFactory& shapeFactory,
        ImageDrawableFactory& imageDrawableFactory,
        TextFormatFactory& textFormatFactory
    ):resourceManager(resourceManager), shapeFactory(shapeFactory), imageDrawableFactory(imageDrawableFactory), textFormatFactory(textFormatFactory) {

        registerClass<ClickableControl>();
        registerClass<SelectableView>();
        registerClass<ClickResponseView>();
        registerClass<StateIndicator>();
        /*registerClass<TextBlock>([&dwriteFactory] {
            return ghnew TextBlock(std::make_unique<TextLayout>(dwriteFactory, L"text", Color(0.0f,0.0f,0.0f), nullptr));
        });
        registerClass<TextView>([&dwriteFactory] {
            return ghnew TextView(std::make_unique<TextLayout>(dwriteFactory, L"text", Color(0.0f, 0.0f, 0.0f), nullptr));
        });
        registerClass<TextField>([&dwriteFactory] {
            return ghnew TextField(std::make_unique<TextLayout>(dwriteFactory, L"text", Color(0.0f, 0.0f, 0.0f), nullptr));
        });*/
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
            return imageDrawableFactory.makeDrawable(path);
        }
        return nullptr;
    }

    Layout* LayoutLoader::load(Ghurund::Core::ResourceManager& manager, MemoryInputStream& stream, const ResourceFormat* format, LoadOption options) {
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)stream.Data, stream.Size);
        SharedPointer<Layout> layout = makeResource<Layout>();

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (child && strcmp(child->Value(), "layout") == 0) {
            layout->Controls.addAll(loadControls(*child));
            if (layout->Controls.Empty) {
                Logger::log(LogType::WARNING, _T("Layout is empty.\n"));
                throw InvalidDataException("Layout is empty.\n");
            }
        } else {
            Logger::log(LogType::ERR0R, _T("Missing 'layout' tag\n"));
            throw InvalidDataException("Missing 'layout' tag\n");
        }

        layout->addReference();
        return layout;
    }

    PointerList<Control*> LayoutLoader::loadControls(const tinyxml2::XMLElement& xml) {
        PointerList<Control*> list;
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            if (strcmp(child->Value(), "include") == 0) {
                auto layoutAttr = child->FindAttribute("layout");
                if (layoutAttr) {
                    AString s = layoutAttr->Value();
                    try {
                        SharedPointer<Layout> layout = resourceManager.load<Layout>(convertText<char, wchar_t>(s), &Layout::FORMATS[0], LoadOption::DONT_CACHE);
                        if (!layout->Controls.Empty) {
                            list.addAll(layout->Controls);
                        } else {
                            Logger::log(LogType::ERR0R, _T("Layout '{}' is empty.\n"), s);
                        }
                    } catch (...) {
                        Logger::log(LogType::ERR0R, _T("Could not load layout '{}'.\n"), s);
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
                try {
                    SharedPointer<Layout> layout = resourceManager.load<Layout>(convertText<char, wchar_t>(s), &Layout::FORMATS[0], LoadOption::DONT_CACHE);
                    if (layout->Controls.Size == 1) {
                        control = layout->Controls[0];
                        control->addReference();
                    } else {
                        Logger::log(LogType::ERR0R, _T("Layout '{}' has to contain exactly one child.\n"), s);
                    }
                } catch (...) {
                    Logger::log(LogType::ERR0R, _T("Could not load layout '{}'.\n"), s);
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
        AString desc = str;
        return shapeFactory.makeShape(desc);
    }

    ColorAttr* LayoutLoader::loadColor(const char* str) {
        AString s = str;
        s = s.trim();
        s.replace('\\', '/');
        if (s.startsWith("#")) {
            return ghnew ColorValue(Color::parse(s));
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
        if (alignmentParam)
            *alignment = Alignment::parse(alignmentParam->Value());

        return Status::OK;
    }
}