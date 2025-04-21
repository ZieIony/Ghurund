#pragma once

#include "DxMesh.h"
#include "core/resource/Loader.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class MeshLoader:public Loader {
    private:
        Graphics& graphics;
        CommandList& commandList;

    public:
        MeshLoader(Graphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}

        virtual DxMesh* load(
            Ghurund::Core::MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format = ResourceFormat::AUTO,
            Ghurund::Core::LoadOption options = LoadOption::DEFAULT
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