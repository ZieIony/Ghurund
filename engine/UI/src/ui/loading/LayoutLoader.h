#pragma once

#include "core/NotNull.h"
#include "core/exception/Exceptions.h"
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
		// borrowed
		Ghurund::Core::ResourceManager* resourceManager;
		// borrowed
		ShapeFactory* shapeFactory;
		// borrowed
		IDrawableFactory* drawableFactory;
		// borrowed
		TextFormatFactory* textFormatFactory;
		// borrowed
		ConstraintFactory* constraintFactory;
		PropertyLoaderCollection propertyLoaders;
		Map<AString, const BaseConstructor*> types;

	protected:
		virtual Resource* loadInternal(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

	public:
		static inline const char* FILE_PROTOCOL = "file://";
		static inline const char* THEME_COLOR = "theme://color/";
		static inline const char* THEME_DRAWABLE = "theme://drawable/";
		static inline const char* THEME_TEXTFORMAT = "theme://textFormat/";

		LayoutLoader(
			NotNull<Ghurund::Core::ResourceManager> resourceManager,
			NotNull<ShapeFactory> shapeFactory,
			NotNull<IDrawableFactory> drawableFactory,
			NotNull<TextFormatFactory> textFormatFactory,
			NotNull<ConstraintFactory> constraintFactory
		);

		virtual ~LayoutLoader() {}

		inline Ghurund::Core::ResourceManager* getResourceManager() {
			return resourceManager;
		}

		__declspec(property(get = getResourceManager)) Ghurund::Core::ResourceManager* ResourceManager;

		template<Derived<Control> T>
		inline void registerType() {
			const Core::Type& type = T::TYPE;
			const BaseConstructor* constructor = type.Constructors.findBySignature<>();
			if (!constructor)
				throw InvalidParamException("the type doesn't have a zero-parameter constructor");
			types.put(type.Namespace + "::" + type.Name, constructor);
		}

		void loadProperties(Object& obj, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		void loadProperty(Object& obj, const BaseProperty& property, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		List<ControlWithConstraints> loadControls(ControlParent& parent, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		ControlWithConstraints loadControl(ControlParent& parent, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		Constraint* loadConstraint(const tinyxml2::XMLElement& xml, Orientation orientation);

		Constraint* loadConstraint(const char* str, Orientation orientation);

		TextFormatRef* loadTextFormat(const char* str);

        void loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);

        DocumentElement* loadDocumentElement(const tinyxml2::XMLElement& xml) {
            return nullptr;
        }
    };
}