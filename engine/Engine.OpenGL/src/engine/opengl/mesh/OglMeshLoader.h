#pragma once

#include "OglMesh.h"

#include "core/loading/Loader.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    class OglMeshLoader:public Loader<OglMesh> {
    private:
        MeshDataLoader meshDataLoader;

    protected:
        virtual void loadInternal(
            OglMesh& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            Ghurund::Core::LoadOption options
        ) override;
    };
}
