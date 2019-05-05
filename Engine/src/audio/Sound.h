#pragma once

#include "resource/Resource.h"
#include "Audio.h"
#include <Shlwapi.h>
#include "collection/List.h"

namespace Ghurund {
	enum class PlaybackState {
		STOPPED, PAUSED, PLAYING
	};

    class Sound: public Resource {
    private:
        IXAudio2SourceVoice* sourceVoice;
        WAVEFORMATEX* waveFormat;
        unsigned int waveFormatLength;
        List<BYTE> audioData;
        XAUDIO2_BUFFER audioBuffer;
		PlaybackState state = PlaybackState::STOPPED;

        Status setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        Status readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        Status loadData(ResourceContext &context, MemoryInputStream &stream, LoadOption options);

    protected:
        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) override;

        virtual Status saveInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const override {
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

        Status stop() {
			if (state == PlaybackState::STOPPED)
				return Status::INV_STATE;
		
			if(isPlaying())
				sourceVoice->Stop();
			if (state != PlaybackState::STOPPED) {
				sourceVoice->FlushSourceBuffers();
				state = PlaybackState::STOPPED;
				return Status::OK;
			}
		}

		inline Status pause() {
			if (state != PlaybackState::PLAYING)
				return Status::INV_STATE;

			sourceVoice->Stop();
			state = PlaybackState::PAUSED;
			return Status::OK;
		}

		inline bool isPlaying() {
			return state == PlaybackState::PLAYING;
		}

        virtual const Ghurund::Type &getType() const override {
            return Type::SOUND;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::WAV};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;
    };
}