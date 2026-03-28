#pragma once

#include "TileSet.h"

#include "core/loading/Loader.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class TileSetLoader:public Loader<TileSet> {
    private:
        ResourceManager& resourceManager;

    protected:
        virtual void loadInternal(
            TileSet& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

    public:
        TileSetLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
    };
}
