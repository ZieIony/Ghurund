#include "ghepch.h"
#include "SoundLoader.h"

#include "Sound.h"

namespace Ghurund {
    Resource* SoundLoader::loadInternal(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        Sound* sound = makeResource<Sound>();
        //sound->load(workingDir, stream, options);
        return sound;
    }

    void SoundLoader::saveInternal(
        MemoryOutputStream& stream,
        const DirectoryPath& workingDir,
        Resource& resource,
        const ResourceFormat& format,
        SaveOption options
    ) const {
        Sound& sound = (Sound&)resource;
        //sound.save(DirectoryPath(_T(".")), stream, options);
    }
}