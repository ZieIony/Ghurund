#include "ghedxpch.h"
#include "DxMeshLoader.h"

namespace Ghurund::Engine::DirectX {
    void DxMeshLoader::loadAssimp(DxMesh& mesh, MemoryInputStream& stream) {
        auto meshData = makeIntrusive<MeshData>();
        meshDataLoader->loadAssimp(meshData.ref(), stream);
        mesh.Data = meshData.get();
    }

    void DxMeshLoader::loadMesh(DxMesh& mesh, MemoryInputStream& stream) {
        readHeader<Mesh>(stream, Mesh::FORMAT_MESH);
        auto meshData = makeIntrusive<MeshData>();
        meshDataLoader->loadMesh(meshData.ref(), stream);
        mesh.Data = meshData.get();
    }

    void DxMeshLoader::saveMesh(DxMesh& resource, MemoryOutputStream& stream) const {
        writeHeader<Mesh>(stream, Mesh::FORMAT_MESH);
        meshDataLoader->saveMesh(*resource.Data, stream);
    }

    CoroutineTask<void> DxMeshLoader::init_internal(DxMesh& resource) {
        resource.init(memoryManager);
        co_return;
    }
}
