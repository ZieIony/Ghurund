#include "ghepch.h"
#include "Audio.h"

#include "core/exception/Exceptions.h"
#include "core/logging/Logger.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"

#include <mfapi.h>
#include <x3daudio.h>
#include <xaudio2.h>

namespace Ghurund::Engine {
    using namespace ::DirectX;
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& Audio::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Audio>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Audio::onInit() {
        if (FAILED(MFStartup(MF_VERSION))) {
            Logger::log(LogType::ERR0R, _T("Failed start the Windows Media Foundation\n"));
            throw CallFailedException();
        }

        // set media foundation reader to low latency
        if (FAILED(MFCreateAttributes(sourceReaderConfiguration.GetAddressOf(), 1))) {
            Logger::log(LogType::ERR0R, _T("Unable to create Media Foundation Source Reader configuration\n"));
            throw CallFailedException();
        }

        if (FAILED(sourceReaderConfiguration->SetUINT32(MF_LOW_LATENCY, true))) {
            Logger::log(LogType::ERR0R, _T("Unable to set Windows Media Foundation configuration\n"));
            throw CallFailedException();
        }

        uint32_t flags = 0;
        if (FAILED(XAudio2Create(device.GetAddressOf(), flags))) {
            Logger::log(LogType::ERR0R, _T("Failed to init XAudio2 engine\n"));
            throw CallFailedException();
        }

#ifdef _DEBUG
        // To see the trace output, you need to view ETW logs for this application:
        //    Go to Control Panel, Administrative Tools, Event Viewer.
        //    View->Show Analytic and Debug Logs.
        //    Applications and Services Logs / Microsoft / Windows / XAudio2. 
        //    Right click on Microsoft Windows XAudio2 debug logging, Properties, then Enable Logging, and hit OK 
        XAUDIO2_DEBUG_CONFIGURATION debug = { 0 };
        debug.TraceMask = XAUDIO2_LOG_ERRORS | XAUDIO2_LOG_WARNINGS;
        debug.BreakMask = XAUDIO2_LOG_ERRORS;
        device->SetDebugConfiguration(&debug, 0);
#endif

        if (FAILED(device->CreateMasteringVoice(&masteringVoice))) {
            device.Reset();
            Logger::log(LogType::ERR0R, _T("Failed creating mastering voice\n"));
            throw CallFailedException();
        }

        masteringVoice->GetVoiceDetails(&outputDetails);
        memset(&dspSettings, 0, sizeof(dspSettings));
        dspSettings.SrcChannelCount = 1;
        dspSettings.DstChannelCount = Channels;
        matrixCoefficients = new float[64];
		//memset(&matrixCoefficients, 0, sizeof(float) * 64);
        dspSettings.pMatrixCoefficients = matrixCoefficients;
        delayTimes = new float[64];
        //memset(&delayTimes, 0, sizeof(float) * 64);
        dspSettings.pDelayTimes = delayTimes;

        DWORD dwChannelMask;
        masteringVoice->GetChannelMask(&dwChannelMask);
        X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance);
    }

    void Audio::onUninit() {
        MFShutdown();

        delete[] matrixCoefficients;
        delete[] delayTimes;
        if (masteringVoice != nullptr) {
            masteringVoice->DestroyVoice();
            masteringVoice = nullptr;
        }
        device.Reset();
    }
}
