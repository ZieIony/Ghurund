#pragma once

#include "DxMesh.h"

#include "core/loading/Loader.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxMeshLoader:public Loader<DxMesh> {
    private:
        DxGPUMemoryManager& memoryManager;
        IntrusivePointer<MeshDataLoader> meshDataLoader;

		void loadAssimp(DxMesh& mesh, MemoryInputStream& stream);
		void loadMesh(DxMesh& mesh, MemoryInputStream& stream);

		void saveMesh(DxMesh& resource, MemoryOutputStream& stream) const;

    protected:
		[[nodiscard]]
		virtual CoroutineTask<void> load_internal(
			DxMesh& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const Ghurund::Core::ResourceFormat& format,
			Ghurund::Core::LoadOptions options
		) override {
			if (format == Mesh::FORMAT_MESH) {
				loadMesh(resource, stream);
			} else if (format == ResourceFormat::AUTO) {
				try {
					loadMesh(resource, stream);
				} catch (...) {
					loadAssimp(resource, stream);
				}
			} else {
				loadAssimp(resource, stream);
			}
			co_return;
		}

        [[nodiscard]]
        virtual CoroutineTask<void> init_internal(DxMesh& resource) override;

		[[nodiscard]]
		void save_internal(
			DxMesh& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const Ghurund::Core::ResourceFormat& format,
			Ghurund::Core::SaveOptions options
		) const {
			if (format == Mesh::FORMAT_MESH)
				saveMesh(resource, stream);
		}

        virtual const ResourceFormat& getPreferredSaveFormat() const override {
            return Mesh::FORMAT_MESH;
        }

    public:
        DxMeshLoader(
            DxGPUMemoryManager& memoryManager
		):memoryManager(memoryManager), meshDataLoader(makeIntrusive<MeshDataLoader>()) {
		}
    };
}
