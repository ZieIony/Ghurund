#pragma once

#include "Material.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine {

	class MaterialLoader:public Ghurund::Core::Loader<Material> {
	private:
		ResourceManager& resourceManager;
		IGPUMemoryManager& memoryManager;
		Material* defaultMaterial = nullptr;

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

		~MaterialLoader() {
			if (defaultMaterial)
				defaultMaterial->release();
		}

		inline void setDefaultMaterial(Material* material) {
			setPointer(defaultMaterial, material);
		}

		inline Material* getDefaultMaterial() const {
			return defaultMaterial;
		}

		__declspec(property(get = getDefaultMaterial, put = setDefaultMaterial)) Material* DefaultMaterial;
	};
}
