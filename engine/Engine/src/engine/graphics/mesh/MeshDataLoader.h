#pragma once

#include "MeshData.h"

#include "core/object/RefCountedObject.h"

namespace Ghurund::Engine {
    class MeshDataLoader:public RefCountedObject {
    public:
        void loadAssimp(MeshData& mesh, MemoryInputStream& stream);
        void loadMesh(MeshData& mesh, MemoryInputStream& stream);

        void saveMesh(MeshData& resource, MemoryOutputStream& stream) const;
    };
}
