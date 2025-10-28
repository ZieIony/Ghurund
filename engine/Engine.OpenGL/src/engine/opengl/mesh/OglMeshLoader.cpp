#include "gheoglpch.h"
#include "OglMeshLoader.h"
#include "OglMesh.h"

namespace Ghurund::Engine::OpenGL {
    Resource* OglMeshLoader::loadInternal(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        Ghurund::Core::LoadOption options
    ) {
        OglMesh* mesh = makeResource<OglMesh>();
        MeshData* meshData = (MeshData*)meshDataLoader.load(stream, workingDir, format, options);
        mesh->init(*meshData);
        meshData->release();
        return mesh;
    }
}