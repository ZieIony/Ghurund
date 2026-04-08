#pragma once

#include "Material.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine {

	class MaterialLoader:public Ghurund::Core::Loader<Material> {
	protected:
		ResourceManager& resourceManager;
		IGPUMemoryManager& memoryManager;

		virtual CoroutineTask<void> loadInternal(
			Material& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) override;

		virtual CoroutineTask<void> onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value);

		virtual void saveInternal(
			Material& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOption options
		) const override;

	public:
		MaterialLoader(
			ResourceManager& resourceManager,
			IGPUMemoryManager& memoryManager
		):resourceManager(resourceManager), memoryManager(memoryManager) {
		}
	};
}