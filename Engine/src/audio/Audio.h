#pragma once

#include "Ghurund.h"

#include <wrl\client.h>

#include <xaudio2.h>
#pragma comment(lib,"xaudio2.lib")

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

using Microsoft::WRL::ComPtr;;

namespace Ghurund {
    class Audio {
    private:
        ComPtr<IXAudio2> device;
        IXAudio2MasteringVoice* masteringVoice = nullptr;
        ComPtr<IMFAttributes> sourceReaderConfiguration;

    public:
        ~Audio() {
            uninit();
        }

        Status init();
        void uninit();

        ComPtr<IXAudio2> getDevice() {
            return device;
        }

        __declspec(property(get = getDevice)) ComPtr<IXAudio2> Device;

        ComPtr<IMFAttributes> getReaderConfiguration() {
            return sourceReaderConfiguration;
        }

        __declspec(property(get = getReaderConfiguration)) ComPtr<IMFAttributes> ReaderConfiguration;
    };
}