#pragma once

#include "TextureAtlas.h"

#include "core/loading/Loader.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class TextureAtlasLoader:public Loader {
    private:
        ResourceManager& resourceManager;

    protected:
        virtual TextureAtlas* loadFromXmlInternal(
            const tinyxml2::XMLElement& xml,
            const DirectoryPath& workingDir,
            LoadOption options
        ) override;

        virtual TextureAtlas* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            return loadFromXml<TextureAtlas>(stream, workingDir, options);
        }

    public:
        TextureAtlasLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
    };
}
