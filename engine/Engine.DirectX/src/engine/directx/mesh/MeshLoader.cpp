#include "ghedxpch.h"
#include "MeshLoader.h"

namespace Ghurund::Engine::DirectX {
    Resource* MeshLoader::loadInternal(
        NotNull<Ghurund::Core::MemoryInputStream> stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        Ghurund::Core::LoadOption options
    ) {
        DxMesh* mesh = makeResource<DxMesh>();
        MeshData* meshData = (MeshData*)meshDataLoader.load(stream, workingDir, format, options);
        mesh->init(*meshData, graphics, commandList);
        meshData->release();
        return mesh;
    }
}