#pragma once

#include "TileMap.h"

#include "core/loading/Loader.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class TileMapLoader:public Loader<TileMap> {
    private:
        ResourceManager& resourceManager;

    protected:
        virtual CoroutineTask<void> loadInternal(
            TileMap& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

    public:
        TileMapLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
    };
}
