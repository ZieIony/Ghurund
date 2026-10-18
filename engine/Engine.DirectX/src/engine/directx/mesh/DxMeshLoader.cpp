#include "ghedxpch.h"
#include "DxMeshLoader.h"

namespace Ghurund::Engine::DirectX {
    CoroutineTask<void> DxMeshLoader::load_internal(
        DxMesh& resource,
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        Ghurund::Core::LoadOptions options
    ) {
        auto meshData = makeIntrusive<MeshData>();
        co_await meshDataLoader->load(meshData.ref(), stream, workingDir, format, options);
        resource.setMeshData(meshData.get());
    }

    CoroutineTask<void> DxMeshLoader::init_internal(DxMesh& resource) {
        resource.init(memoryManager);
        co_return;
    }
}
