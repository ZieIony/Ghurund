#pragma once

#include "DxMesh.h"
#include "core/resource/Loader.h"
#include <engine/graphics/mesh/MeshDataLoader.h>

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class MeshLoader:public Loader {
    private:
        Graphics& graphics;
        CommandList& commandList;
        MeshDataLoader meshDataLoader;

    protected:
        virtual Resource* loadInternal(
            NotNull<Ghurund::Core::MemoryInputStream> stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            Ghurund::Core::LoadOption options
        ) override;

    public:
        MeshLoader(Graphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}
    };
}