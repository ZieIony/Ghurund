#pragma once

#include "core/exception/Exceptions.h"
#include "core/loading/Loader.h"
#include "core/loading/PropertyLoaderCollection.h"
#include "core/resource/ResourceManager.h"
#include "engine/graphics/texture/ITextureFactory.h"
#include "ui/Alignment.h"
#include "ui/constraint/ConstraintFactory.h"
#include "ui/control/Control.h"
#include "ui/layout/ControlWithConstraints.h"
#include "ui/text/DocumentElement.h"

#include <tinyxml2.h>
#include <ui/theme/ThemedValue.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class TextFormat;
	class Theme;

	class LayoutLoader :public Ghurund::Core::Loader {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = LayoutLoader::GET_TYPE();
#pragma endregion

	private:
		Ghurund::Core::ResourceManager& resourceManager;
		ITextureFactory& textureFactory;
		ConstraintFactory& constraintFactory;
		PropertyLoaderCollection propertyLoaders;
		Map<AString, const BaseConstructor*> types;

		static inline const AString DEFAULT_CONTROL_NAMESPACE = LayoutLoader::TYPE.Namespace;

	protected:
		virtual Resource* loadInternal(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

	public:
		static inline const char* FILE_PROTOCOL = "file://";
		static inline const char* THEME_TEXT_STYLE = "theme://textStyle/";

		LayoutLoader(
			Ghurund::Core::ResourceManager& resourceManager,
			ITextureFactory& textureFactory,
			ConstraintFactory& constraintFactory
		);

		virtual ~LayoutLoader() {}

		inline Ghurund::Core::ResourceManager& getResourceManager() {
			return resourceManager;
		}

		__declspec(property(get = getResourceManager)) Ghurund::Core::ResourceManager& ResourceManager;

		inline PropertyLoaderCollection& getPropertyLoaders() {
			return propertyLoaders;
		}

		__declspec(property(get = getPropertyLoaders)) PropertyLoaderCollection& PropertyLoaders;

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

		ThemedTextStyle* loadTextStyle(const char* str);

        void loadAlignment(const tinyxml2::XMLElement& xml, Alignment* alignment);

        DocumentElement* loadDocumentElement(const tinyxml2::XMLElement& xml) {
            return nullptr;
        }
    };
}