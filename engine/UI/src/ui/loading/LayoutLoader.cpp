#include "ghuipch.h"
#include "LayoutLoader.h"

#include "StringPropertyLoader.h"
#include "PrimitivePropertyLoaders.h"
#include "ColorPropertyLoaders.h"
#include "DrawablePropertyLoader.h"
#include "ImageScaleModePropertyLoader.h"
#include "TextDocumentPropertyLoader.h"
#include "core/logging/Formatter.h"
#include "core/string/TextConversionUtils.h"

// control types to register
#include "ui/adapter/AdapterLayout.h"
#include "ui/constraint/ConstraintLayout.h"
#include "ui/control/ScrollView.h"
#include "ui/layout/VerticalLayout.h"
#include "ui/layout/HorizontalLayout.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/button/IconButton.h"
#include "ui/widget/menu/MenuBar.h"
#include "ui/widget/toolbar/Toolbar.h"
#include "ui/text/TextBlock.h"
#include "ui/text/TextView.h"
#include "ui/text/TextField.h"

#include "LayoutPropertyLoader.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& LayoutLoader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<LayoutLoader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    LayoutLoader::LayoutLoader(
        Ghurund::Core::ResourceManager& resourceManager,
        IDrawableFactory& drawableFactory,
        TextFormatFactory& textFormatFactory,
        ConstraintFactory& constraintFactory
    ):resourceManager(resourceManager), drawableFactory(drawableFactory),
        textFormatFactory(textFormatFactory), constraintFactory(constraintFactory)
    {
        propertyLoaders.add(std::make_unique<BoolPropertyLoader>());
        propertyLoaders.add(std::make_unique<UInt32PropertyLoader>());
        propertyLoaders.add(std::make_unique<FloatPropertyLoader>());
        propertyLoaders.add(std::make_unique<AStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<NullableAStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<WStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<ColorPropertyLoader>());
        propertyLoaders.add(std::make_unique<NullableColorPropertyLoader>());
		propertyLoaders.add(std::make_unique<ImageScaleModePropertyLoader>());
		propertyLoaders.add(std::unique_ptr<PropertyLoader>(ghnew DrawablePropertyLoader(drawableFactory)));
		propertyLoaders.add(std::make_unique<TextDocumentPropertyLoader>());
		propertyLoaders.add(std::unique_ptr<LayoutPropertyLoader>(ghnew LayoutPropertyLoader(resourceManager, *this)));

		for (const Core::Type& type : Type::TYPES) {
			const BaseConstructor* constructor = type.Constructors.findBySignature<>();
			types.put(type.Namespace + "::" + type.Name, constructor);
		}
	}

	Resource* LayoutLoader::loadInternal(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
		tinyxml2::XMLDocument doc;
		doc.Parse((const char*)stream.Data, stream.Size);

        tinyxml2::XMLElement* child = doc.FirstChildElement();
        if (!child) {
            Logger::log(LogType::ERR0R, _T("Missing control tag.\n"));
            throw InvalidFormatException("Missing control tag.\n");
        }
        AString namespaceName = DEFAULT_CONTROL_NAMESPACE;
        auto namespaceAttr = child->FindAttribute("namespace");
        if (namespaceAttr)
            namespaceName = namespaceAttr->Value();
		AString type = namespaceName + "::" + child->Value();
        const BaseConstructor* constructor = types.get(type);
        if (!constructor)
            throw InvalidDataException(std::format("No zero-argument constructor found for '{}'.\n", type).c_str());
        Control* control = (Control*)constructor->invokeRaw();
        control->load(*this, workingDir, *child);
        return control;
    }

    void LayoutLoader::loadProperties(Object& obj, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        const Core::Type* type = &obj.Type;
        while (*type != RefCountedObject::TYPE) {
            for (auto& property : type->Properties) {
                if (property.get().CanWrite)
                    loadProperty(obj, property, workingDir, xml);
            }
            type = type->Supertype;
        }
    }

    void LayoutLoader::loadProperty(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        AString propertyName = property.Name;
        AString propertyUpper = propertyName.substring(0, 1).toUpperCase() + propertyName.substring(1);
        AString propertyLower = propertyName.substring(0, 1).toLowerCase() + propertyName.substring(1);
        const Core::Type& type = obj.Type;
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
            loader->loadAttr(obj, property, workingDir, propertyAttr->Value());
        } else if (propertyElement) {
            if (!propertyElement->FirstAttribute() &&
                !propertyElement->NoChildren() &&
                !propertyElement->FirstChildElement() &&
                propertyElement->FirstChild()) {
                loader->loadAttr(obj, property, workingDir, propertyElement->GetText());
            } else if (!propertyElement->FirstAttribute() && !propertyElement->NoChildren()) {
                loader->loadChildren(obj, property, workingDir, *propertyElement->FirstChildElement());
            } else {
                loader->loadElement(obj, property, workingDir, *propertyElement);
            }
        }
    }

    List<ControlWithConstraints> LayoutLoader::loadControls(ControlParent& parent, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        List<ControlWithConstraints> list;
        const tinyxml2::XMLElement* childElement = xml.FirstChildElement();
        while (childElement) {
            if (!AString(childElement->Name()).contains("."))
                list.add(loadControl(parent, workingDir, *childElement));
			childElement = childElement->NextSiblingElement();
        }
        return list;
    }

    ControlWithConstraints LayoutLoader::loadControl(ControlParent& parent, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
        const char* name = xml.Value();
        if (strcmp(name, "include") == 0) {
            auto layoutAttr = xml.FindAttribute("layout");
            if (layoutAttr) {
                AString s = layoutAttr->Value();
                try {
                    IntrusivePointer<Control> control(resourceManager.load<Control>(
                        FilePath(convertText<char, wchar_t>(s)), workingDir, Control::FORMAT_XML, LoadOption::DONT_CACHE)
                    );
                    PartialConstraintSet loadedConstraints;
                    loadedConstraints.load(control->Type, *this, xml);
                    PartialConstraintSet constraints = parent.makeDefaultConstraints();
                    constraints.merge(loadedConstraints);
                    return ControlWithConstraints(control, constraints);
                } catch (...) {
                    auto text = std::format(_T("Could not load layout '{}'.\n"), s);
					Logger::log(LogType::ERR0R, text.c_str());
				}
			}
			Logger::log(LogType::ERR0R, _T("Missing 'layout' attribute.\n"));
			throw InvalidDataException("Missing 'layout' attribute.\n");
		} else {
			AString namespaceName = DEFAULT_CONTROL_NAMESPACE;
			auto namespaceAttr = xml.FindAttribute("namespace");
			if (namespaceAttr)
				namespaceName = namespaceAttr->Value();
			AString type = namespaceName + "::" + xml.Value();
			const BaseConstructor* constructor = types[type];
			if (constructor) {
				IntrusivePointer<Control> control((Control*)constructor->invokeRaw());
				control->load(*this, workingDir, xml);
                PartialConstraintSet loadedConstraints;
                loadedConstraints.load(control->Type, *this, xml);
                PartialConstraintSet constraints = parent.makeDefaultConstraints();
                constraints.merge(loadedConstraints);
				return ControlWithConstraints(control, constraints);
			} else {
				Logger::log(LogType::ERR0R, std::format(_T("{} is not a known control or it doesn't declare a zero argument constructor.\n"), type).c_str());
				throw InvalidDataException(std::format("{} is not a known control or it doesn't declare a zero argument constructor.\n", type).c_str());
			}
		}
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

    TextFormatRef* LayoutLoader::loadTextFormat(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        if (s.startsWith(FILE_PROTOCOL)) {
            //auto textFormat = ghnew TextFormat()
        } else if (s.startsWith(THEME_TEXTFORMAT)) {
            TextFormatKey textFormatKey = s.substring(lengthOf(THEME_TEXTFORMAT));
            return ghnew TextFormatRef(textFormatKey);
        }
        return nullptr;
    }

    void LayoutLoader::loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment) {
        auto alignmentParam = xml.FindAttribute("alignment");
        if (alignmentParam)
            *alignment = Alignment::parse(alignmentParam->Value());
    }
}