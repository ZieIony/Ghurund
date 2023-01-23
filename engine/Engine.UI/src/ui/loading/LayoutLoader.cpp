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
#include "ui/layout/constraint/ConstraintLayout.h"
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
        TextFormatFactory& textFormatFactory,
        ConstraintFactory& constraintFactory
    ):resourceManager(resourceManager), shapeFactory(shapeFactory), imageDrawableFactory(imageDrawableFactory), textFormatFactory(textFormatFactory), constraintFactory(constraintFactory) {}

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

    Control* LayoutLoader::load(Ghurund::Core::ResourceManager& manager, MemoryInputStream& stream, const ResourceFormat* format, LoadOption options) {
        tinyxml2::XMLDocument doc;
        doc.Parse((const char*)stream.Data, stream.Size);

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (!child) {
            Logger::log(LogType::ERR0R, _T("Missing control tag.\n"));
            throw InvalidFormatException("Missing control tag.\n");
        }
        AString namespaceName = Ghurund::UI::NAMESPACE_NAME;
        auto namespaceAttr = child->FindAttribute("namespace");
        if (namespaceAttr)
            namespaceName = namespaceAttr->Value();
        const Type& type = Type::byName(namespaceName, child->Value());
        const BaseConstructor* constructor = type.getConstructors().findBySignature<>();
        if (!constructor)
            throw InvalidDataException(std::format("No zero-argument constructor found for '{}'.\n", type).c_str());
        Control* control = (Control*)constructor->invokeRaw();
        control->load(*this, *child);
        return control;
    }

    PointerList<Control*> LayoutLoader::loadControls(const tinyxml2::XMLElement& xml) {
        PointerList<Control*> list;
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            Control* control = loadControl(*child);
            if (control) {
                list.add(control);
                control->release();
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
                    SharedPointer<Control> control = resourceManager.load<Control>(convertText<char, wchar_t>(s), &Control::FORMATS[0], LoadOption::DONT_CACHE);
                    control->addReference();
                } catch (...) {
                    Logger::log(LogType::ERR0R, _T("Could not load layout '{}'.\n"), s);
                }
                return control;
            }
            Logger::log(LogType::ERR0R, _T("Missing 'layout' attribute.\n"));
            return nullptr;
        } else {
            AString namespaceName = Ghurund::UI::NAMESPACE_NAME;
            auto namespaceAttr = xml.FindAttribute("namespace");
            if (namespaceAttr)
                namespaceName = namespaceAttr->Value();
            try {
                const Type& type = Type::byName(namespaceName, xml.Value());
                if (type.isOrExtends(Control::GET_TYPE())) {
                    const BaseConstructor* constructor = type.getConstructors().findBySignature<>();
                    if (!constructor)
                        throw InvalidDataException(std::format("No zero-argument constructor found for '{}'.\n", type).c_str());
                    Control* control = (Control*)constructor->invokeRaw();
                    control->load(*this, xml);
                    return control;
                } else {
                    // it's a known class, but not a control
                    return nullptr;
                }
            } catch (TypeNotFoundException exception) {
            }
        }
        Logger::log(LogType::WARNING, _T("Control type {} not registered in LayoutLoader.\n"), convertText<char, tchar>(AString(name)));
        return nullptr;
    }

    Constraint* LayoutLoader::loadConstraint(const tinyxml2::XMLElement& xml) {
        AString name, ratio, offset, min, max;
        auto nameAttr = xml.FindAttribute("path");
        if (nameAttr)
            name = nameAttr->Value();
        auto ratioAttr = xml.FindAttribute("ratio");
        if (ratioAttr)
            ratio = ratioAttr->Value();
        auto offsetAttr = xml.FindAttribute("offset");
        if (offsetAttr)
            offset = offsetAttr->Value();
        auto minAttr = xml.FindAttribute("min");
        if (minAttr)
            min = minAttr->Value();
        auto maxAttr = xml.FindAttribute("max");
        if (maxAttr)
            max = maxAttr->Value();
        return constraintFactory.parseConstraint(
            nameAttr ? &name: nullptr,
            ratioAttr ? &ratio : nullptr,
            offsetAttr ? &offset : nullptr,
            minAttr ? &min : nullptr,
            maxAttr ? &max : nullptr
        );
    }

    Constraint* LayoutLoader::loadConstraint(const char* str) {
        return constraintFactory.parseConstraint(str);
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