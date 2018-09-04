#pragma once

#include "resource/Resource.h"
#include "Audio.h"
#include <Shlwapi.h>
#include "collection/List.h"

namespace Ghurund {
    class Sound: public Resource {
    private:
        IXAudio2SourceVoice* sourceVoice;
        WAVEFORMATEX* waveFormat;
        unsigned int waveFormatLength;
        List<BYTE> audioData;
        XAUDIO2_BUFFER audioBuffer;

        Status setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        Status readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        Status loadData(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options);

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, MemoryInputStream &stream, LoadOption options) override;

        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override {
            return Status::NOT_IMPLEMENTED;
        }

        virtual unsigned int getVersion() const {
            return 0;
        }

    public:
        ~Sound() {
            sourceVoice->DestroyVoice();
        }

        Status play();

        void stop() {
            sourceVoice->Stop();
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::SOUND;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::WAV};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::WAV;
        }
    };
}