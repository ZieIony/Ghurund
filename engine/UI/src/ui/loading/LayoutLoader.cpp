#include "ghuipch.h"
#include "LayoutLoader.h"

#include "ColorPropertyLoaders.h"
#include "ImageScaleModePropertyLoader.h"
#include "LayoutPropertyLoader.h"
#include "TextDocumentPropertyLoader.h"
#include "TexturePropertyLoader.h"

#include "core/loading/PrimitivePropertyLoaders.h"
#include "core/loading/StringPropertyLoader.h"
#include "core/logging/Formatter.h"
#include "core/string/TextConversionUtils.h"

// control types to register
#include "ui/adapter/AdapterLayout.h"
#include "ui/constraint/ConstraintLayout.h"
#include "ui/control/ImageView.h"
#include "ui/control/ScrollView.h"
#include "ui/layout/HorizontalLayout.h"
#include "ui/layout/VerticalLayout.h"
#include "ui/text/TextBlock.h"
#include "ui/text/TextField.h"
#include "ui/text/TextView.h"
#include "ui/widget/button/Button.h"
#include "ui/widget/button/IconButton.h"
#include "ui/widget/menu/MenuBar.h"
#include "ui/widget/toolbar/Toolbar.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& LayoutLoader::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<LayoutLoader>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    LayoutLoader::LayoutLoader(
        Ghurund::Core::ResourceManager& resourceManager,
        ConstraintFactory& constraintFactory
	):resourceManager(resourceManager), constraintFactory(constraintFactory) {
        propertyLoaders.add(std::make_unique<BoolPropertyLoader>());
        propertyLoaders.add(std::make_unique<UInt32PropertyLoader>());
        propertyLoaders.add(std::make_unique<FloatPropertyLoader>());
        propertyLoaders.add(std::make_unique<AStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<NullableAStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<WStringPropertyLoader>());
        propertyLoaders.add(std::make_unique<ColorPropertyLoader>());
        propertyLoaders.add(std::make_unique<NullableColorPropertyLoader>());
		propertyLoaders.add(std::make_unique<ImageScaleModePropertyLoader>());
		propertyLoaders.add(std::unique_ptr<PropertyLoader>(ghnew TexturePropertyLoader(resourceManager)));
		//propertyLoaders.add(std::make_unique<TextDocumentPropertyLoader>());
		propertyLoaders.add(std::unique_ptr<LayoutPropertyLoader>(ghnew LayoutPropertyLoader(resourceManager, *this)));

		for (const Core::Type& type : Type::TYPES) {
			const BaseConstructor* constructor = type.Constructors.findBySignature<>();
			types.put(type.Namespace + "::" + type.Name, constructor);
		}
	}

	void LayoutLoader::loadInternal(
        Control& resource,
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        XMLDocument doc;
		doc.parse(stream.Data, stream.Size);
        // TODO: check root name and version

        const XMLElement& child = doc.Root;
        AString namespaceName = DEFAULT_CONTROL_NAMESPACE;
        auto namespaceAttr = child.findAttribute(L"namespace");
        if (namespaceAttr)
            namespaceName = convertText<wchar_t, char>(*namespaceAttr);
		AString type = namespaceName + "::" + convertText<wchar_t, char>(child.name);

        resource.load(*this, workingDir, child);
    }

    void LayoutLoader::loadProperties(Object& obj, const DirectoryPath& workingDir, const XMLElement& xml) {
        const Core::Type* type = &obj.Type;
        while (*type != RefCountedObject::TYPE) {
            for (auto& property : type->Properties) {
                if (property.get().CanWrite)
                    loadProperty(obj, property, workingDir, xml);
            }
            type = type->Supertype;
        }
    }

    void LayoutLoader::loadProperty(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const XMLElement& xml) {
        AString propertyName = property.Name;
        AString propertyUpper = propertyName.substring(0, 1).toUpperCase() + propertyName.substring(1);
        AString propertyLower = propertyName.substring(0, 1).toLowerCase() + propertyName.substring(1);
        const Core::Type& type = obj.Type;
        auto elementName = std::format(L"{}.{}", type.Name, propertyUpper);

        const XMLElement* propertyElement = xml.findElement(elementName.c_str());
        auto propertyAttr = xml.findAttribute(convertText<char, wchar_t>(propertyLower.Data));

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
            loader->loadAttr(obj, property, workingDir, convertText<wchar_t, char>(*propertyAttr));
        } else if (propertyElement) {
            if (!propertyElement->value.Empty) {
                loader->loadAttr(obj, property, workingDir, convertText<wchar_t, char>(propertyElement->value));
            } else if (propertyElement->attributes.Empty && !propertyElement->children.Empty) {
                loader->loadChildren(obj, property, workingDir, propertyElement->children[0].ref());
            } else {
                loader->loadElement(obj, property, workingDir, *propertyElement);
            }
        }
    }

    List<ControlWithConstraints> LayoutLoader::loadControls(ControlParent& parent, const DirectoryPath& workingDir, const XMLElement& xml) {
        List<ControlWithConstraints> list;
        for(const auto& childElement : xml.children){
            if (!childElement->name.contains(L"."))
                list.add(loadControl(parent, workingDir, childElement.ref()));
        }
        return list;
    }

    ControlWithConstraints LayoutLoader::loadControl(ControlParent& parent, const DirectoryPath& workingDir, const XMLElement& xml) {
        const WString& name = xml.name;
        if (name == L"include") {
            auto layoutAttr = xml.findAttribute(L"layout");
            if (layoutAttr) {
                WString s = *layoutAttr;
                try {
                    IntrusivePointer<Control> control(resourceManager.load<Control>(
                        FilePath(s), workingDir, Control::FORMAT_XML, LoadOption::DONT_CACHE)
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
			auto namespaceAttr = xml.findAttribute(L"namespace");
			if (namespaceAttr)
				namespaceName = convertText<wchar_t, char>(*namespaceAttr);
			AString type = namespaceName + "::" + convertText<wchar_t, char>(name);
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

	Constraint* LayoutLoader::loadConstraint(const XMLElement& xml, Orientation orientation) {
        AString name, ratio, offset, min, max;
        auto nameAttr = xml.findAttribute(L"path");
        if (nameAttr)
            name = convertText<wchar_t, char>(*nameAttr);
        auto ratioAttr = xml.findAttribute(L"ratio");
        if (ratioAttr)
            ratio = convertText<wchar_t, char>(*ratioAttr);
        auto offsetAttr = xml.findAttribute(L"offset");
        if (offsetAttr)
            offset = convertText<wchar_t, char>(*offsetAttr);
        auto minAttr = xml.findAttribute(L"min");
        if (minAttr)
            min = convertText<wchar_t, char>(*minAttr);
        auto maxAttr = xml.findAttribute(L"max");
        if (maxAttr)
            max = convertText<wchar_t, char>(*maxAttr);
        return constraintFactory.parseConstraint(
            nameAttr ? &name : nullptr,
            ratioAttr ? &ratio : nullptr,
            offsetAttr ? &offset : nullptr,
            minAttr ? &min : nullptr,
            maxAttr ? &max : nullptr,
            orientation
        );
    }

    Constraint* LayoutLoader::loadConstraint(const AString& str, Orientation orientation) {
        return constraintFactory.parseConstraint(str, orientation);
    }

    ThemedTextStyle* LayoutLoader::loadTextStyle(const char* str) {
        AString s = str;
        s.replace('\\', '/');
        if (s.startsWith(FILE_PROTOCOL)) {
            //auto font = ghnew Font()
        } else if (s.startsWith(THEME_TEXT_STYLE)) {
            TextStyleKey textStyleKey = s.substring(lengthOf(THEME_TEXT_STYLE));
            return ghnew ThemedTextStyle(textStyleKey);
        }
        return nullptr;
    }

    void LayoutLoader::loadAlignment(const XMLElement& xml, Alignment* alignment) {
        auto alignmentParam = xml.findAttribute(L"alignment");
        if (alignmentParam)
            *alignment = Alignment::parse(convertText<wchar_t, char>(*alignmentParam));
    }
}