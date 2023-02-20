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
#include "ui/drawable/ImageDrawable.h"
#include "ui/loading/ShapeFactory.h"
#include "ui/loading/ImageDrawableFactory.h"
#include "ui/loading/TextFormatFactory.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/style/ColorAttr.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class TextFormat;
	class Theme;
	class Shape;

	class LayoutLoader :public Ghurund::Core::Loader {
	private:
		Ghurund::Core::ResourceManager& resourceManager;
		Theme* theme = nullptr;
		ShapeFactory& shapeFactory;
		ImageDrawableFactory& imageDrawableFactory;
		TextFormatFactory& textFormatFactory;
		ConstraintFactory& constraintFactory;
		PropertyLoaderCollection propertyLoaders;

	public:
		static inline const char* FILE_PROTOCOL = "file://";
		static inline const char* THEME_STYLE = "theme://style/";
		static inline const char* THEME_COLOR = "theme://color/";
		static inline const char* THEME_IMAGE = "theme://image/";
		static inline const char* THEME_TEXTFORMAT = "theme://textFormat/";

		LayoutLoader(
			Ghurund::Core::ResourceManager& resourceManager,
			ShapeFactory& shapeFactory,
			ImageDrawableFactory& imageDrawableFactory,
			TextFormatFactory& textFormatFactory,
			ConstraintFactory& constraintFactory
		);

		virtual ~LayoutLoader() {}

		inline Theme* getTheme() {
			return theme;
		}

		inline void setTheme(Theme* theme) {
			this->theme = theme;
		}

		__declspec(property(get = getTheme, put = setTheme)) Theme* Theme;

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
			Ghurund::Core::ResourceManager& manager,
			Ghurund::Core::MemoryOutputStream& stream,
			Ghurund::Core::Resource& resource,
			const Ghurund::Core::ResourceFormat* format = nullptr,
			Ghurund::Core::SaveOption options = Ghurund::Core::SaveOption::DEFAULT
		) const override {
			throw NotImplementedException();
		}

		void loadProperties(Object& obj, const tinyxml2::XMLElement& xml) {
			const Type* type = &obj.Type;
			while (*type != Pointer::TYPE) {
				for (auto& property : type->Properties) {
					if (property.get().CanWrite)
						loadProperty(obj, property, xml);
				}
				type = type->Supertype;
			}
		}

		void loadProperty(Object& obj, const BaseProperty& property, const tinyxml2::XMLElement& xml);

		PointerList<Control*> loadControls(const tinyxml2::XMLElement& xml);

		Control* loadControl(const tinyxml2::XMLElement& xml);

		Constraint* loadConstraint(const tinyxml2::XMLElement& xml, Orientation orientation);

		Constraint* loadConstraint(const char* str, Orientation orientation);

		TextFormat* loadTextFormat(const char* str);

		Status loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);
	};
}