#pragma once

#include "Audio.h"

#include "core/loading/Loader.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class SoundLoader:public Loader {
    private:
        Audio& audio;

    protected:
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

    public:
        SoundLoader(Audio& audio):audio(audio) {}
    };
}