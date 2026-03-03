#pragma once

#include "TileSet.h"

#include "core/loading/Loader.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine::_2D {
    using namespace Ghurund::Core;

    class TileSetLoader:public Loader {
    private:
        ResourceManager& resourceManager;

    protected:
        virtual TileSet* loadFromXmlInternal(
            const tinyxml2::XMLElement& xml,
            const DirectoryPath& workingDir,
            LoadOption options
        ) override;

        virtual TileSet* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            return loadFromXml<TileSet>(stream, workingDir, options);
        }

    public:
        TileSetLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
    };
}
