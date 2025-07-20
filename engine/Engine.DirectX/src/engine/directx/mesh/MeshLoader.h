#pragma once

#include "DxMesh.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class MeshLoader:public Loader {
    private:
        Graphics& graphics;
        CommandList& commandList;

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        MeshLoader(Graphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}
    };
}