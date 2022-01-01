#include "ghpch.h"
#include "MeshLoader.h"

namespace Ghurund {
    Mesh* MeshLoader::load(ResourceManager& manager, MemoryInputStream& stream, const ResourceFormat* format, LoadOption options) {
        Mesh* mesh = makeResource<Mesh>();
        //mesh->load(DirectoryPath(_T(".")), stream, options);
        mesh->init(graphics, commandList);
        return mesh;
    }
    
    void MeshLoader::save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, const ResourceFormat* format, SaveOption options) const {
        Mesh& mesh = (Mesh&)resource;
        //mesh.save(DirectoryPath(_T(".")), stream, options);
    }
}