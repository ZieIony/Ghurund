#include "ghepch.h"
#include "Sound.h"

#include "Common.h"
#include "core/logging/Logger.h"
#include "core/reflection/TypeBuilder.h"

#include <wrl\client.h>

#include <xaudio2.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

namespace Ghurund {
    using namespace Ghurund::Core;
    using Microsoft::WRL::ComPtr;

	/*void Sound::loadInternal(const DirectoryPath &workingDir, MemoryInputStream & stream, LoadOption options) {
        Status result = loadData(context, stream, options);
        if(result!=Status::OK)
            return result;

        if(FAILED(context.Audio.Device->CreateSourceVoice(&sourceVoice, waveFormat)))
            return Logger::log(LogType::WARNING, Status::CALL_FAIL, _T("Unable to create source voice\n"));

        memset(&audioBuffer, 0, sizeof(XAUDIO2_BUFFER));
        audioBuffer.AudioBytes = (uint32_t)audioData.Size;
        audioBuffer.pAudioData = (BYTE* const)&audioData[0];
        audioBuffer.pContext = nullptr;
        audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
        audioBuffer.LoopCount = XAUDIO2_NO_LOOP_REGION;

        throw NotImplementedException();
    }*/

    void Sound::setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex) {
        ComPtr<IMFMediaType> partialType = nullptr;
        if (FAILED(MFCreateMediaType(partialType.GetAddressOf()))) {
            Logger::log(LogType::ERR0R, _T("Unable to create media type\n"));
            throw CallFailedException();
        }

        if (FAILED(partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio))) {
            Logger::log(LogType::ERR0R, _T("Unable to set media type to audio\n"));
            throw CallFailedException();
        }

        // request uncompressed data
        if (FAILED(partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM))) {
            Logger::log(LogType::ERR0R, _T("Unable to set guid of media type to uncompressed\n"));
            throw CallFailedException();
        }

        if (FAILED(sourceReader->SetCurrentMediaType(streamIndex, nullptr, partialType.Get()))) {
            Logger::log(LogType::ERR0R, _T("Unable to set current media type\n"));
            throw CallFailedException();
        }
    }

    void Sound::readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex) {
        ComPtr<IMFSample> sample = nullptr;
        ComPtr<IMFMediaBuffer> buffer = nullptr;
        BYTE* localAudioData = NULL;
        DWORD localAudioDataLength = 0;

        while(true) {
            DWORD flags = 0;
            if (FAILED(sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, sample.GetAddressOf()))) {
                Logger::log(LogType::ERR0R, _T("Unable to read audio sample\n"));
                throw CallFailedException();
            }

            // check whether the data is still valid
            if(flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
                break;

            // check for eof
            if(flags & MF_SOURCE_READERF_ENDOFSTREAM)
                break;

            if(sample == nullptr)
                continue;

            // convert data to contiguous buffer
            if (FAILED(sample->ConvertToContiguousBuffer(buffer.GetAddressOf()))) {
                Logger::log(LogType::ERR0R, _T("Unable to convert audio sample to contiguous buffer\n"));
                throw CallFailedException();
            }

            // lock buffer and copy data to local memory
            if (FAILED(buffer->Lock(&localAudioData, nullptr, &localAudioDataLength))) {
                Logger::log(LogType::ERR0R, _T("Critical error: Unable to lock the audio buffer\n"));
                throw CallFailedException();
            }

            for(size_t i = 0; i < localAudioDataLength; i++)
                audioData.add(localAudioData[i]);

            localAudioData = nullptr;

            if(FAILED(buffer->Unlock())) {
                Logger::log(LogType::ERR0R, _T("Critical error while unlocking the audio buffer\n"));
                throw CallFailedException();
            }
        }
    }

    void Sound::loadData(MemoryInputStream & stream, LoadOption options) {
        /*Audio &audio = context.Audio;

        ComPtr<IStream> memStream = SHCreateMemStream((const BYTE *)stream.Data, (UINT)stream.Size);
        ComPtr<IMFByteStream> spMFByteStream = nullptr;
        MFCreateMFByteStreamOnStreamEx((IUnknown*)memStream.Get(), &spMFByteStream);

        ComPtr<IMFSourceReader> sourceReader;
        if(FAILED(MFCreateSourceReaderFromByteStream(spMFByteStream.Get(), audio.ReaderConfiguration.Get(), sourceReader.GetAddressOf())))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to create source reader\n"));

        if(FAILED(sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to disable streams\n"));

        DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;
        if(FAILED(sourceReader->SetStreamSelection(streamIndex, true)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to enable first audio stream\n"));

        Microsoft::WRL::ComPtr<IMFMediaType> nativeMediaType;
        if(FAILED(sourceReader->GetNativeMediaType(streamIndex, 0, nativeMediaType.GetAddressOf())))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to query media information\n"));

        GUID majorType{};
        HRESULT hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
        if(majorType != MFMediaType_Audio)
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("The requested file is not an audio file\n"));

        GUID subType{};
        hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
        if(subType != MFAudioFormat_Float && subType != MFAudioFormat_PCM)
            setupDecompression(sourceReader, streamIndex);

        // uncompress the data and load it into an XAudio2 Buffer
        Microsoft::WRL::ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
        if(FAILED(sourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf())))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to retrieve the current media type\n"));

        if(FAILED(MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType.Get(), &waveFormat, &waveFormatLength)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to create the wave format\n"));

        if(FAILED(sourceReader->SetStreamSelection(streamIndex, true)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to select audio stream\n"));

        return readSamples(sourceReader, streamIndex);*/
    }

    const Ghurund::Core::Type& Sound::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Sound>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

	void Sound::play() {
		if (state == PlaybackState::PLAYING)
			throw InvalidStateException();

		if (state == PlaybackState::STOPPED) {
            if (FAILED(sourceVoice->SubmitSourceBuffer(&audioBuffer))) {
                Logger::log(LogType::ERR0R, _T("Unable to submit source buffer\n"));
                throw CallFailedException();
            }
		}

        if (FAILED(sourceVoice->Start())) {
            Logger::log(LogType::ERR0R, _T("Unable to start playback\n"));
            throw CallFailedException();
        }

        state = PlaybackState::PLAYING;
	}
}