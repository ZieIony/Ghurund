module;

#include "core/Exceptions.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/directx/MathTypes.h"
#include "core/logging/Logger.h"

#include <xaudio2.h>
#include <mfapi.h>
#include <x3daudio.h>

module Ghurund.Engine.Audio.Audio;

namespace Ghurund::Audio {
    using namespace ::DirectX;
    using namespace Ghurund::Core;

    const Ghurund::Core::Type& Audio::GET_TYPE() {
        static auto PROPERTY_POSITION = Ghurund::Core::Property<Audio, XMFLOAT3>("Position", (XMFLOAT3(Audio::*)()) & getPosition, (void(Audio::*)(XMFLOAT3)) & setPosition);
        static auto PROPERTY_VELOCITY = Ghurund::Core::Property<Audio, XMFLOAT3>("Velocity", (XMFLOAT3(Audio::*)()) & getVelocity, (void(Audio::*)(XMFLOAT3)) & setVelocity);
        static auto PROPERTY_DIRECTION = Ghurund::Core::Property<Audio, XMFLOAT3>("Direction", (XMFLOAT3(Audio::*)()) & getDirection, (void(Audio::*)(XMFLOAT3)) & setDirection);
        static auto PROPERTY_UP = Ghurund::Core::Property<Audio, XMFLOAT3>("Up", (XMFLOAT3(Audio::*)()) & getUp, (void(Audio::*)(XMFLOAT3)) & setUp);

        static const auto CONSTRUCTOR = Constructor<Audio>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Audio>("Ghurund::Audio", "Audio")
            .withProperty(PROPERTY_POSITION)
            .withProperty(PROPERTY_VELOCITY)
            .withProperty(PROPERTY_DIRECTION)
            .withProperty(PROPERTY_UP)
            .withConstructor(CONSTRUCTOR)
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

        DWORD dwChannelMask;
        masteringVoice->GetChannelMask(&dwChannelMask);
        X3DAudioInitialize(dwChannelMask, X3DAUDIO_SPEED_OF_SOUND, x3DInstance);
    }

    void Audio::onUninit() {
        MFShutdown();

        if (masteringVoice != nullptr) {
            masteringVoice->DestroyVoice();
            masteringVoice = nullptr;
        }
        device.Reset();
    }
}