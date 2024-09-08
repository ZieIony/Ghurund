#include "ghedxpch.h"
#include "MeshLoader.h"

namespace Ghurund {
    Mesh* MeshLoader::load(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        Mesh* mesh = makeResource<Mesh>();
        //mesh->load(DirectoryPath(_T(".")), stream, options);
        mesh->init(graphics, commandList);
        return mesh;
    }
    
    void MeshLoader::save(
        MemoryOutputStream& stream,
        const DirectoryPath& workingDir,
        Resource& resource,
        const ResourceFormat& format,
        SaveOption options
    ) const {
        Mesh& mesh = (Mesh&)resource;
        //mesh.save(DirectoryPath(_T(".")), stream, options);
    }
}