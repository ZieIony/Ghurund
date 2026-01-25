#pragma once

#include "Material.h"

#include "core/loading/Loader.h"

#include <tinyxml2.h>

namespace Ghurund::Engine {

	class MaterialLoader:public Ghurund::Core::Loader {
	protected:
		ResourceManager& resourceManager;
		IGPUMemoryManager& memoryManager;

		virtual Material* makeMaterial();

		virtual void onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value);

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
			IGPUMemoryManager& memoryManager
		):resourceManager(resourceManager), memoryManager(memoryManager) {
		}

		Material* loadFromXml(const tinyxml2::XMLElement& xml, const DirectoryPath& workingDir);
	};
}