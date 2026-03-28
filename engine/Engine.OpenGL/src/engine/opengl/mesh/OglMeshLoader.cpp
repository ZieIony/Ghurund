#include "gheoglpch.h"
#include "OglMeshLoader.h"
#include "OglMesh.h"

namespace Ghurund::Engine::OpenGL {
    void OglMeshLoader::loadInternal(
        OglMesh& resource,
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        Ghurund::Core::LoadOption options
    ) {
        auto meshData = makeIntrusive<MeshData>();
        meshDataLoader.load(meshData.ref(), stream, workingDir, format, options);
        resource.init(meshData.ref());
    }
}
