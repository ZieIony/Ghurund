#pragma once

#include "core/resource/Loader.h"
#include <engine/graphics/mesh/MeshDataLoader.h>

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

    class OglMeshLoader:public Loader {
    private:
        MeshDataLoader meshDataLoader;

    protected:
        virtual Resource* loadInternal(
            NotNull<Ghurund::Core::MemoryInputStream> stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            Ghurund::Core::LoadOption options
        ) override;
    };
}