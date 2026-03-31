#include "ghepch.h"
#include "Sound.h"

#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include <xaudio2.h>

namespace Ghurund::Engine {
    using namespace Ghurund::Core;
    using Microsoft::WRL::ComPtr;

    const Ghurund::Core::Type& Sound::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Sound>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Sound::invalidate() {
        __super::invalidate();

        if (sourceVoice) {
            sourceVoice->DestroyVoice();
            sourceVoice = nullptr;
        }
        if (waveFormat) {
            CoTaskMemFree(waveFormat);
            waveFormat = nullptr;
        }
        delete audioBuffer.pAudioData;
        memset(&audioBuffer, 0, sizeof(XAUDIO2_BUFFER));
    }

    void Sound::play() {
        if (IsPlaying)
            return;

        if (FAILED(sourceVoice->SubmitSourceBuffer(&audioBuffer))) {
            Logger::log(LogType::ERR0R, _T("Unable to submit source buffer\n"));
            throw CallFailedException();
        }

        if (FAILED(sourceVoice->Start())) {
            Logger::log(LogType::ERR0R, _T("Unable to start playback\n"));
            throw CallFailedException();
        }
	}
}