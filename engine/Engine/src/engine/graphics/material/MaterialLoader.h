#pragma once

#include "Material.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine {

	class MaterialLoader:public Ghurund::Core::Loader<Material> {
	private:
		ResourceManager& resourceManager;
		IGPUMemoryManager& memoryManager;

		CoroutineTask<void> loadXmlFormat(Material& resource, const XMLElement& xml, const DirectoryPath& workingDir);

	protected:
		virtual CoroutineTask<void> load_internal(
			Material& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) override;

		virtual CoroutineTask<void> onLoadParameter(Material& material, const DirectoryPath& workingDir, MaterialInput& input, const AString& value);

		[[nodiscard]]
		virtual CoroutineTask<void> init_internal(Material& resource) {
			resource.init(memoryManager);
			co_return;
		}

		[[nodiscard]]
		virtual CoroutineTask<void> deinit_internal(Material& resource) {
			resource.deinit();
			co_return;
		}

		[[nodiscard]]
		virtual CoroutineTask<void> unload_internal(Material& resource) {
			resource.unload();
			co_return;
		}

		virtual void save_internal(
			Material& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const override;

	public:
		MaterialLoader(
			ResourceManager& resourceManager,
			IGPUMemoryManager& memoryManager
		):resourceManager(resourceManager), memoryManager(memoryManager) {
		}
	};
}
