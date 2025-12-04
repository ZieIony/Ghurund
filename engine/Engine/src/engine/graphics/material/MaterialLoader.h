#pragma once

#include "core/resource/Loader.h"
#include "IMaterialFactory.h"
#include "engine/graphics/texture/ITextureFactory.h"

#include <tinyxml2.h>

namespace Ghurund::Engine {

	class MaterialLoader:public Ghurund::Core::Loader {
	private:
		ResourceManager& resourceManager;
		IMaterialFactory& materialFactory;
		ITextureFactory& textureFactory;

	public:
		MaterialLoader(
			ResourceManager& resourceManager,
			IMaterialFactory& materialFactory,
			ITextureFactory& textureFactory
		):resourceManager(resourceManager), materialFactory(materialFactory), textureFactory(textureFactory) {
		}

		IMaterial* loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir);
	};
}