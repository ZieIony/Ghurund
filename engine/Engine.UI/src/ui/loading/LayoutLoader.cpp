#include "ghuipch.h"
#include "LayoutLoader.h"

#include "StringPropertyLoader.h"
#include "PrimitivePropertyLoaders.h"
#include "ColorPropertyLoaders.h"
#include "ShapePropertyLoader.h"
#include "DrawablePropertyLoader.h"
#include "ImageScaleModePropertyLoader.h"
#include "TextDocumentPropertyLoader.h"
#include "core/logging/Formatter.h"
#include "core/string/TextConversionUtils.h"
#include "ui/control/Clip.h"
#include "ui/control/Space.h"
#include "ui/style/Theme.h"

#include <ranges>

namespace Ghurund::UI {

    LayoutLoader::LayoutLoader(
        Ghurund::Core::ResourceManager& resourceManager,
        ShapeFactory& shapeFactory,
        ImageDrawableFactory& imageDrawableFactory,
        TextFormatFactory& textFormatFactory,
        ConstraintFactory& constraintFactory
    ):resourceManager(resourceManager), shapeFactory(shapeFactory), imageDrawableFactory(imageDrawableFactory), textFormatFactory(textFormatFactory), constraintFactory(constraintFactory) {
        propertyLoaders.add(std::make_unique<BoolPropertyLoader>());
        propertyLoaders.add(std::make_unique<UInt32PropertyLoader>());
        propertyLoaders.add(std::make_unique<FloatPropertyLoader>());
        propertyLoaders.add(std::make_unique<AStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<NullableAStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<WStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<ColorPropertyLoader>());
        propertyLoaders.add(std::make_unique<NullableColorPropertyLoader>());
        propertyLoaders.add(std::make_unique<ImageScaleModePropertyLoader>());
        propertyLoaders.add(std::unique_ptr<PropertyLoader>(ghnew ShapePropertyLoader(shapeFactory)));
        propertyLoaders.add(std::unique_ptr<PropertyLoader>(ghnew DrawablePropertyLoader(imageDrawableFactory)));
        propertyLoaders.add(std::make_unique<TextDocumentPropertyLoader>());
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

    void LayoutLoader::loadProperty(Object& obj, const BaseProperty& property, const tinyxml2::XMLElement& xml) {
        AString propertyName = property.Name;
        AString propertyUpper = propertyName.substring(0, 1).toUpperCase() + propertyName.substring(1);
        AString propertyLower = propertyName.substring(0, 1).toLowerCase() + propertyName.substring(1);
        const Type& type = obj.Type;
        auto elementName = std::format("{}.{}", type.Name, propertyUpper);

        const tinyxml2::XMLElement* propertyElement = xml.FirstChildElement(elementName.c_str());
        auto propertyAttr = xml.FindAttribute(propertyLower.Data);

        if (propertyAttr && propertyElement) {
            auto text = std::format("A combination of both - '{}' attribute and '{}.{}' child is invalid.", propertyLower, type.Name, propertyUpper);
            throw InvalidDataException(text.c_str());
        } else if (!propertyAttr && !propertyElement) {
            return;
        }

        PropertyLoader* loader = propertyLoaders.get(property.Type);
        if (!loader) {
            Logger::log(LogType::WARNING, std::format(_T("No loader for type {}::{}.\n"), property.Type.Namespace, property.Type.Name).c_str());
            return;
        }

        if (propertyAttr) {
            loader->loadAttr(obj, property, propertyAttr->Value());
        } else if (propertyElement) {
            if (!propertyElement->FirstAttribute() &&
                !propertyElement->NoChildren() &&
                !propertyElement->FirstChildElement() &&
                propertyElement->FirstChild()) {
                loader->loadAttr(obj, property, propertyElement->GetText());
            } else if (!propertyElement->FirstAttribute() && !propertyElement->NoChildren()) {
                loader->loadChildren(obj, property, *propertyElement);
            } else {
                loader->loadElement(obj, property, *propertyElement);
            }
        }
    }

    PointerList<Control*> LayoutLoader::loadControls(const tinyxml2::XMLElement& xml) {
        PointerList<Control*> list;
        const tinyxml2::XMLElement* childElement = xml.FirstChildElement();
        while (childElement) {
            if (!AString(childElement->Name()).contains(".")) {
                Control* control = loadControl(*childElement);
                if (control) {
                    list.add(control);
                    control->release();
                } else {
                    Logger::log(LogType::WARNING, std::format(_T("Failed to load control {}.\n"), AString(childElement->Name())).c_str());
                }
            }
            childElement = childElement->NextSiblingElement();
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
                    SharedPointer<Control> control(resourceManager.load<Control>(convertText<char, wchar_t>(s), &Control::FORMATS[0], LoadOption::DONT_CACHE));
                    control->addReference();
                } catch (...) {
                    auto text = std::format(_T("Could not load layout '{}'.\n"), s);
                    Logger::log(LogType::ERR0R, text.c_str());
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
        auto text = std::format(_T("Control type {} not registered in LayoutLoader.\n"), AString(name));
        Logger::log(LogType::WARNING, text.c_str());
        return nullptr;
    }

    Constraint* LayoutLoader::loadConstraint(const tinyxml2::XMLElement& xml, Orientation orientation) {
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
            nameAttr ? &name : nullptr,
            ratioAttr ? &ratio : nullptr,
            offsetAttr ? &offset : nullptr,
            minAttr ? &min : nullptr,
            maxAttr ? &max : nullptr,
            orientation
        );
    }

    Constraint* LayoutLoader::loadConstraint(const char* str, Orientation orientation) {
        return constraintFactory.parseConstraint(str, orientation);
    }

    TextFormat* LayoutLoader::loadTextFormat(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        if (s.startsWith(FILE_PROTOCOL)) {
            //auto textFormat = ghnew TextFormat()
        } else if (s.startsWith(THEME_TEXTFORMAT) && theme) {
            TextFormatKey textFormatKey = s.substring(lengthOf(THEME_TEXTFORMAT));
            if (theme->TextFormats.containsKey(textFormatKey)) {
                TextFormat* style = theme->TextFormats[textFormatKey].get();
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