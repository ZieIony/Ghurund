#pragma once

#include "PropertyLoaderCollection.h"
#include "core/Buffer.h"
#include "core/Exceptions.h"
#include "core/collection/Stack.h"
#include "core/collection/PointerList.h"
#include "core/io/FilePath.h"
#include "core/reflection/Type.h"
#include "core/resource/Loader.h"
#include "core/resource/ResourceManager.h"
#include "core/string/StringView.h"
#include "ui/Alignment.h"
#include "ui/control/Control.h"
#include "ui/loading/ShapeFactory.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/loading/TextFormatFactory.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/style/ColorAttr.h"
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

		virtual Control* load(
			Ghurund::Core::ResourceManager& manager,
			Ghurund::Core::MemoryInputStream& stream,
			const Ghurund::Core::ResourceFormat* format = nullptr,
			Ghurund::Core::LoadOption options = Ghurund::Core::LoadOption::DEFAULT
		) override;

        virtual void save(
            const Ghurund::Core::ResourceManager& manager,
            Ghurund::Core::MemoryOutputStream& stream,
            Ghurund::Core::Resource& resource,
            const Ghurund::Core::ResourceFormat* format = nullptr,
            Ghurund::Core::SaveOption options = Ghurund::Core::SaveOption::DEFAULT
        ) const override {
            throw NotImplementedException();
        }

		void loadProperties(Object& obj, const tinyxml2::XMLElement& xml);

		void loadProperty(Object& obj, const BaseProperty& property, const tinyxml2::XMLElement& xml);

		PointerList<Control*> loadControls(const tinyxml2::XMLElement& xml);

		Control* loadControl(const tinyxml2::XMLElement& xml);

		Constraint* loadConstraint(const tinyxml2::XMLElement& xml, Orientation orientation);

		Constraint* loadConstraint(const char* str, Orientation orientation);

		TextFormatRef* loadTextFormat(const char* str);

        Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);

        DocumentElement* loadDocumentElement(const tinyxml2::XMLElement& xml) {
            return nullptr;
        }
    };
}