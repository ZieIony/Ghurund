#include "ghedxpch.h"
#include "MeshLoader.h"

namespace Ghurund::Engine::DirectX {
    CoroutineTask<void> MeshLoader::loadInternal(
        DxMesh& resource,
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        Ghurund::Core::LoadOption options
    ) {
        auto meshData = makeIntrusive<MeshData>();
        co_await meshDataLoader.load(meshData.ref(), stream, workingDir, format, options);
        resource.init(meshData.ref(), memoryManager);
    }
}