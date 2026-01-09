#pragma once

#include "core/loading/Loader.h"
#include "engine/graphics/mesh/MeshDataLoader.h"

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    class OglMeshLoader:public Loader {
    private:
        MeshDataLoader meshDataLoader;

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            Ghurund::Core::LoadOption options
        ) override;
    };
}