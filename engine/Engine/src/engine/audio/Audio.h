#pragma once

#include "core/feature/Feature.h"

#include <wrl\client.h>

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")
#include <x3daudio.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <DirectXMath.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

namespace Ghurund::Engine {
    using namespace ::DirectX;
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::Core;

    class Audio:public Noncopyable, public Object, public Initializable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Audio::GET_TYPE();
#pragma endregion

    private:
        ComPtr<IXAudio2> device;
        // can there be more than one mastering voice?
        IXAudio2MasteringVoice* masteringVoice = nullptr;
        ComPtr<IMFAttributes> sourceReaderConfiguration;
        X3DAUDIO_DSP_SETTINGS dspSettings = {};
        float* matrixCoefficients = nullptr;
        float* delayTimes = nullptr;
        XAUDIO2_VOICE_DETAILS outputDetails;

        X3DAUDIO_HANDLE x3DInstance;

    public:
        virtual void onInit() override;

        virtual void onUninit() override;

        inline ComPtr<IXAudio2> getDevice() {
            return device;
        }

        __declspec(property(get = getDevice)) ComPtr<IXAudio2> Device;

        inline IXAudio2MasteringVoice* getMasteringVoice() {
            return masteringVoice;
        }

        __declspec(property(get = getMasteringVoice)) IXAudio2MasteringVoice* MasteringVoice;

        inline ComPtr<IMFAttributes> getReaderConfiguration() {
            return sourceReaderConfiguration;
        }

        __declspec(property(get = getReaderConfiguration)) ComPtr<IMFAttributes> ReaderConfiguration;

        inline uint32_t getChannels() const {
            return outputDetails.InputChannels;
        }

        __declspec(property(get = getChannels)) uint32_t Channels;

        inline uint32_t getSampleRate() const {
            return outputDetails.InputSampleRate;
        }

        __declspec(property(get = getSampleRate)) uint32_t SampleRate;

        inline void setVolume(float volume) {
            masteringVoice->SetVolume(volume);
        }

        inline float getVolume() const {
            float volume;
            masteringVoice->GetVolume(&volume);
            return volume;
        }

        __declspec(property(get = getVolume, put = setVolume)) float Volume;

        inline X3DAUDIO_DSP_SETTINGS calculateDSPSettings(const X3DAUDIO_LISTENER& listener, const X3DAUDIO_EMITTER& emitter) {
            uint32_t flags = X3DAUDIO_CALCULATE_MATRIX | X3DAUDIO_CALCULATE_DOPPLER;
            dspSettings.SrcChannelCount = emitter.ChannelCount;
            X3DAudioCalculate(x3DInstance, &listener, &emitter, flags, &dspSettings);
            return dspSettings;
        }
    };
}