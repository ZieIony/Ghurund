#pragma once

#include "core/object/NotNull.h"
#include "core/resource/Resource.h"

#include <xaudio2.h>
#include <x3daudio.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

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
        IXAudio2MasteringVoice* masteringVoice = nullptr;
        XAUDIO2_VOICE_DETAILS outputDetails;
        IXAudio2SourceVoice* sourceVoice = nullptr;
        XAUDIO2_VOICE_DETAILS inputDetails;
        WAVEFORMATEX* waveFormat = nullptr;
        XAUDIO2_BUFFER audioBuffer = {};
        bool loop = false;

    public:
        Sound() {}

		~Sound() {
			if (sourceVoice)
				sourceVoice->DestroyVoice();
            CoTaskMemFree(waveFormat);
			delete audioBuffer.pAudioData;
		}

		virtual void invalidate() override;

        virtual bool getIsValid() const override {
			return __super::getIsValid() && sourceVoice;
		}

        void init(
            NotNull<IXAudio2MasteringVoice> masteringVoice,
            NotNull<IXAudio2SourceVoice> sourceVoice,
            NotNull<WAVEFORMATEX> waveFormat,
			XAUDIO2_BUFFER audioBuffer
		) {
            this->masteringVoice = masteringVoice.get();
            this->masteringVoice->GetVoiceDetails(&outputDetails);
            this->sourceVoice = sourceVoice.get();
            this->sourceVoice->GetVoiceDetails(&inputDetails);
            this->waveFormat = waveFormat.get();
            this->audioBuffer = audioBuffer;
		}

        void play();

        void stop() {
            sourceVoice->ExitLoop();
            sourceVoice->Stop();
            sourceVoice->FlushSourceBuffers();
        }

        inline void pause() {
            sourceVoice->Stop();
        }

        inline bool getIsPlaying() const {
            XAUDIO2_VOICE_STATE voiceState;
            sourceVoice->GetState(&voiceState, 0);
			return voiceState.BuffersQueued > 0;
        }

        __declspec(property(get = getIsPlaying)) bool IsPlaying;

        inline float getPosition() const {
            XAUDIO2_VOICE_STATE voiceState;
            sourceVoice->GetState(&voiceState, 0);
            return (float)voiceState.SamplesPlayed / waveFormat->nSamplesPerSec;
        }

        __declspec(property(get = getPosition)) float Position;

        inline float getLength() const {
            return ((float)(audioBuffer.AudioBytes) / (waveFormat->wBitsPerSample * waveFormat->nChannels / 8)) / waveFormat->nSamplesPerSec;
        }

        __declspec(property(get = getLength)) float Length;

        inline bool getLoop() {
            return audioBuffer.LoopCount == XAUDIO2_LOOP_INFINITE;
        }

        inline void setLoop(bool loop) {
            if (loop) {
                audioBuffer.LoopCount = XAUDIO2_LOOP_INFINITE;
            } else {
                audioBuffer.LoopCount = 0;
            }
        }

        __declspec(property(get = getLoop, put = setLoop)) bool Loop;

        inline uint32_t getChannelCount() const {
            return inputDetails.InputChannels;
        }

        __declspec(property(get = getChannelCount)) uint32_t ChannelCount;

        inline uint32_t getSampleRate() const {
            return inputDetails.InputSampleRate;
        }

        __declspec(property(get = getSampleRate)) uint32_t SampleRate;

        inline void setVolume(float volume) {
            sourceVoice->SetVolume(volume);
        }

        inline float getVolume() const {
            float volume;
            sourceVoice->GetVolume(&volume);
            return volume;
        }

        __declspec(property(get = getVolume, put = setVolume)) float Volume;

        void setDSPSettings(const X3DAUDIO_DSP_SETTINGS& dspSettings);

        __declspec(property(put = setDSPSettings)) const X3DAUDIO_DSP_SETTINGS& DSPSettings;

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