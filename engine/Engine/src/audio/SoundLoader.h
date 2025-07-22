#pragma once

#include "Sound.h"
#include "core/resource/Loader.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class SoundLoader:public Loader {
    private:
        Audio& audio;

    protected:
        virtual Resource* loadInternal(
            NotNull<MemoryInputStream> stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            NotNull<MemoryOutputStream> stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        SoundLoader(Audio& audio):audio(audio) {}
    };
}