#pragma once

#include "SpriteAnimationSet.h"

#include "core/loading/Loader.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteAnimationSetLoader:public Loader<SpriteAnimationSet> {
	private:
        ResourceManager& resourceManager;

        virtual CoroutineTask<void> loadInternal(
            SpriteAnimationSet& resource,
            const XMLElement& xml,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            SpriteAnimationSet& resource,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        List<DirectoryPath> includeDirs;

        SpriteAnimationSetLoader(ResourceManager& resourceManager):resourceManager(resourceManager) {}
	};
}
