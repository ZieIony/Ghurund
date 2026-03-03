#pragma once

#include "TileMap.h"

#include "core/loading/Loader.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class TileMapLoader:public Loader {
    private:
        ResourceManager& resourceManager;

    protected:
        virtual TileMap* loadFromXmlInternal(
            const tinyxml2::XMLElement& xml,
            const DirectoryPath& workingDir,
            LoadOption options
        ) override;

        virtual TileMap* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            return loadFromXml<TileMap>(stream, workingDir, options);
        }

    public:
        TileMapLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
    };
}
