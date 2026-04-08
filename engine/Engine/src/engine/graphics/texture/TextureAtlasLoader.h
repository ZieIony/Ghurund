#pragma once

#include "TextureAtlas.h"

#include "core/loading/Loader.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class TextureAtlasLoader:public Loader<TextureAtlas> {
    private:
        ResourceManager& resourceManager;

    protected:
        virtual CoroutineTask<void> loadInternal(
            TextureAtlas& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

    public:
        TextureAtlasLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
    };
}
