#pragma once

#include "core/Exceptions.h"
#include "core/resource/Loader.h"
#include "core/resource/ResourceManager.h"
#include "PropertyLoaderCollection.h"
#include "ui/Alignment.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/control/Control.h"
#include "ui/layout/ControlWithConstraints.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/loading/ShapeFactory.h"
#include "ui/loading/TextFormatFactory.h"
#include "ui/style/TextFormatAttr.h"
#include "ui/text/DocumentElement.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class TextFormat;
	class Theme;
	class Shape;

	class LayoutLoader :public Ghurund::Core::Loader {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		ShapeFactory& shapeFactory;
		DrawableFactory& drawableFactory;
		TextFormatFactory& textFormatFactory;
		ConstraintFactory& constraintFactory;
		PropertyLoaderCollection propertyLoaders;
		Map<AString, const BaseConstructor*> types;

	public:
		static inline const char* FILE_PROTOCOL = "file://";
		static inline const char* THEME_COLOR = "theme://color/";
		static inline const char* THEME_DRAWABLE = "theme://drawable/";
		static inline const char* THEME_TEXTFORMAT = "theme://textFormat/";

		LayoutLoader(
			Ghurund::Core::ResourceManager& resourceManager,
			ShapeFactory& shapeFactory,
			DrawableFactory& drawableFactory,
			TextFormatFactory& textFormatFactory,
			ConstraintFactory& constraintFactory
		);

		virtual ~LayoutLoader() {}

		inline Ghurund::Core::ResourceManager& getResourceManager() {
			return resourceManager;
		}

		__declspec(property(get = getResourceManager)) Ghurund::Core::ResourceManager& ResourceManager;

		template<Derived<Control> T>
		inline void registerType() {
			const Core::Type& type = T::TYPE;
			const BaseConstructor* constructor = type.Constructors.findBySignature<>();
			if (!constructor)
				throw InvalidParamException("the type doesn't have a zero-parameter constructor");
			types.put(type.Namespace + "::" + type.Name, constructor);
		}

		virtual Control* load(
			Ghurund::Core::MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const Ghurund::Core::ResourceFormat* format = nullptr,
			Ghurund::Core::LoadOption options = Ghurund::Core::LoadOption::DEFAULT
		) override;

        virtual void save(
            Ghurund::Core::MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
            Ghurund::Core::Resource& resource,
            const Ghurund::Core::ResourceFormat* format = nullptr,
            Ghurund::Core::SaveOption options = Ghurund::Core::SaveOption::DEFAULT
        ) const override {
            throw NotImplementedException();
        }

		void loadProperties(Object& obj, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		void loadProperty(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		List<ControlWithConstraints> loadControls(ControlParent& parent, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		ControlWithConstraints loadControl(ControlParent& parent, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		Constraint* loadConstraint(const tinyxml2::XMLElement& xml, Orientation orientation);

		Constraint* loadConstraint(const char* str, Orientation orientation);

		TextFormatRef* loadTextFormat(const char* str);

        Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);

        DocumentElement* loadDocumentElement(const tinyxml2::XMLElement& xml) {
            return nullptr;
        }
    };
}