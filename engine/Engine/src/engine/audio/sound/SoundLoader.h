#pragma once

#include "Sound.h"

#include "core/loading/Loader.h"
#include "engine/audio/Audio.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class SoundLoader:public Loader<Sound> {
    private:
        struct AudioData {
            uint8_t* data;
            uint32_t size;
        };

        Audio& audio;

        void setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        AudioData readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        void loadData(Sound& sound, MemoryInputStream& stream);

    protected:
        virtual void loadInternal(
            Sound& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

    public:
        SoundLoader(Audio& audio):audio(audio) {}
    };
}
