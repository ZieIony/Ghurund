#pragma once

#include "Mesh.h"
#include "core/resource/Loader.h"
#include "core/Exceptions.h"

namespace Ghurund::Engine {
    class MeshLoader:public Loader {
    private:
        struct ObjVert {
            uint32_t posIndex, texCoordIndex, normalIndex, vertexIndex;
        };

        Mesh* loadObj(MemoryInputStream& stream);
        Mesh* loadMesh(MemoryInputStream& stream);

    public:
        virtual Mesh* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format = ResourceFormat::AUTO,
            LoadOption options = LoadOption::DEFAULT
        ) override;

        virtual void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format = ResourceFormat::AUTO,
            SaveOption options = SaveOption::DEFAULT
        ) const override;
    };
}