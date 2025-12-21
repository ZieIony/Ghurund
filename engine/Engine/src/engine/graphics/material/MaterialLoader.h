#pragma once

#include "Material.h"

#include "core/resource/Loader.h"
#include "engine/graphics/texture/ITextureFactory.h"

#include <tinyxml2.h>

namespace Ghurund::Engine {

	class MaterialLoader:public Ghurund::Core::Loader {
	private:
		ResourceManager& resourceManager;
		ITextureFactory& textureFactory;

	protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

		virtual void saveInternal(
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			Resource& resource,
			const ResourceFormat& format,
			SaveOption options
		) const override;

	public:
		MaterialLoader(
			ResourceManager& resourceManager,
			ITextureFactory& textureFactory
		):resourceManager(resourceManager), textureFactory(textureFactory) {
		}

		Material* loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir);
	};
}