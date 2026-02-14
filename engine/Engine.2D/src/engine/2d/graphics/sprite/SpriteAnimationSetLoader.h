#pragma once

#include "SpriteAnimationSet.h"

#include "core/loading/Loader.h"

#include <tinyxml2.h>

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteAnimationSetLoader:public Loader {
	private:
        ResourceManager& resourceManager;

        SpriteAnimationSet* loadFromXml(
            const tinyxml2::XMLElement& xml,
            const DirectoryPath& workingDir,
            LoadOption options
        );

    public:
        List<DirectoryPath> includeDirs;

        SpriteAnimationSetLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}

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
	};
}