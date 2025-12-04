#pragma once

#include "core/collection/Array.h"
#include "core/collection/List.h"
#include "core/resource/Resource.h"

#include <Windows.h>
#include <wrl\client.h>

#include <xaudio2.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

namespace Ghurund {
    using namespace Ghurund::Core;
    using Microsoft::WRL::ComPtr;

    enum class PlaybackState {
        STOPPED, PAUSED, PLAYING
    };

    class Sound: public Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Sound::GET_TYPE();
#pragma endregion

    private:
        IXAudio2SourceVoice* sourceVoice;
        WAVEFORMATEX* waveFormat;
        unsigned int waveFormatLength;
        List<BYTE> audioData;
        XAUDIO2_BUFFER audioBuffer;
        PlaybackState state = PlaybackState::STOPPED;

        void setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        void readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex);
        void loadData(MemoryInputStream& stream, LoadOption options);

    protected:
        //virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;

    public:
        ~Sound() {
            sourceVoice->DestroyVoice();
        }

        virtual void invalidate() override {
            sourceVoice->DestroyVoice();
            sourceVoice = nullptr;

            __super::invalidate();
        }

        virtual bool isValid() const override {
			return __super::isValid() && sourceVoice;
        }

        void play();

        void stop() {
            if (state == PlaybackState::STOPPED)
                throw InvalidStateException();

            if (isPlaying())
                sourceVoice->Stop();
            //if (state != PlaybackState::STOPPED) {
                sourceVoice->FlushSourceBuffers();
                state = PlaybackState::STOPPED;
              //  return Status::OK;
            //}
            //return Status::CALL_FAIL;
        }

        inline void pause() {
            if (state != PlaybackState::PLAYING)
                throw InvalidStateException();

            sourceVoice->Stop();
            state = PlaybackState::PAUSED;
        }

        inline bool isPlaying() const {
            return state == PlaybackState::PLAYING;
        }

        __declspec(property(get = isPlaying)) bool Playing;

        inline float getPosition() const {
            XAUDIO2_VOICE_STATE voiceState;
            sourceVoice->GetState(&voiceState, 0);
            return (float)voiceState.SamplesPlayed / waveFormat->nSamplesPerSec;
        }

        __declspec(property(get = getPosition)) float Position;

        inline float getLength() const {
            return ((float)(audioData.Size) / (waveFormat->wBitsPerSample * waveFormat->nChannels / 8)) / waveFormat->nSamplesPerSec;
        }

        __declspec(property(get = getLength)) float Length;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Sound::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_WAV = ResourceFormat(L"wav", ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_WAV };

        static const inline uint32_t VERSION = 0;
#pragma endregion
    };
}