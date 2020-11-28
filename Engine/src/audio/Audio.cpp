#include "Audio.h"
#include "application/log/Logger.h"

namespace Ghurund::Audio {
    Status Audio::init() {
        if (FAILED(MFStartup(MF_VERSION)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Failed start the Windows Media Foundation\n"));

        // set media foundation reader to low latency
        if (FAILED(MFCreateAttributes(sourceReaderConfiguration.GetAddressOf(), 1)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to create Media Foundation Source Reader configuration\n"));

        if (FAILED(sourceReaderConfiguration->SetUINT32(MF_LOW_LATENCY, true)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to set Windows Media Foundation configuration\n"));

        uint32_t flags = 0;
        if (FAILED(XAudio2Create(device.GetAddressOf(), flags)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Failed to init XAudio2 engine\n"));

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
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Failed creating mastering voice\n"));
        }

        DWORD dwChannelMask;
        masteringVoice->GetChannelMask(&dwChannelMask);
        X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance);

        return Status::OK;
    }

    void Audio::uninit() {
        MFShutdown();

        if (masteringVoice != nullptr) {
            masteringVoice->DestroyVoice();
            masteringVoice = nullptr;
        }
        device.Reset();
    }
}