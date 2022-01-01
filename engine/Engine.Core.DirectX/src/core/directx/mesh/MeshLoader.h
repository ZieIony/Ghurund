#pragma once

#include "Mesh.h"
#include "core/resource/Loader.h"
#include "core/Exceptions.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class MeshLoader:public Loader {
    private:
        Graphics& graphics;
        CommandList& commandList;

    public:
        MeshLoader(Graphics& graphics, CommandList& commandList):graphics(graphics), commandList(commandList) {}

        virtual Mesh* load(
            ResourceManager& manager,
            MemoryInputStream& stream,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override;

        virtual void save(
            ResourceManager& manager,
            MemoryOutputStream& stream,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override;
    };
}