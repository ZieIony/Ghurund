#include "ghpch.h"

#include "Sound.h"

#include "Ghurund.Engine.h"
#include "Common.h"
#include "Status.h"

#include <wrl\client.h>

#include <xaudio2.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#include "core/logging/Logger.h"

namespace Ghurund::Audio {
    using namespace Ghurund::Core;
    using Microsoft::WRL::ComPtr;

	void Sound::loadInternal(const DirectoryPath &workingDir, MemoryInputStream & stream, LoadOption options) {
        /*Status result = loadData(context, stream, options);
        if(result!=Status::OK)
            return result;

        if(FAILED(context.Audio.Device->CreateSourceVoice(&sourceVoice, waveFormat)))
            return Logger::log(LogType::WARNING, Status::CALL_FAIL, _T("Unable to create source voice\n"));

        memset(&audioBuffer, 0, sizeof(XAUDIO2_BUFFER));
        audioBuffer.AudioBytes = (uint32_t)audioData.Size;
        audioBuffer.pAudioData = (BYTE* const)&audioData[0];
        audioBuffer.pContext = nullptr;
        audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
        audioBuffer.LoopCount = XAUDIO2_NO_LOOP_REGION;*/

        throw NotImplementedException();
    }

    Status Sound::setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex) {
        ComPtr<IMFMediaType> partialType = nullptr;
        if(FAILED(MFCreateMediaType(partialType.GetAddressOf())))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to create media type\n"));

        if(FAILED(partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to set media type to audio\n"));

        // request uncompressed data
        if(FAILED(partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to set guid of media type to uncompressed\n"));

        if(FAILED(sourceReader->SetCurrentMediaType(streamIndex, nullptr, partialType.Get())))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to set current media type\n"));

        return Status::OK;
    }

    Status Sound::readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex) {
        ComPtr<IMFSample> sample = nullptr;
        ComPtr<IMFMediaBuffer> buffer = nullptr;
        BYTE* localAudioData = NULL;
        DWORD localAudioDataLength = 0;

        while(true) {
            DWORD flags = 0;
            if(FAILED(sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, sample.GetAddressOf())))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to read audio sample\n"));

            // check whether the data is still valid
            if(flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
                break;

            // check for eof
            if(flags & MF_SOURCE_READERF_ENDOFSTREAM)
                break;

            if(sample == nullptr)
                continue;

            // convert data to contiguous buffer
            if(FAILED(sample->ConvertToContiguousBuffer(buffer.GetAddressOf())))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to convert audio sample to contiguous buffer\n"));

            // lock buffer and copy data to local memory
            if(FAILED(buffer->Lock(&localAudioData, nullptr, &localAudioDataLength)))
                return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Critical error: Unable to lock the audio buffer\n"));

            for(size_t i = 0; i < localAudioDataLength; i++)
                audioData.add(localAudioData[i]);

            localAudioData = nullptr;

            if(FAILED(buffer->Unlock())) {
                Logger::log(LogType::ERR0R, _T("Critical error while unlocking the audio buffer\n"));
                return Status::CALL_FAIL;
            }
        }

        return Status::OK;
    }

    Status Sound::loadData(MemoryInputStream & stream, LoadOption options) {
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
        return Status::OK;
    }

    const Ghurund::Core::Type& Sound::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Sound>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Sound>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Sound))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

	Status Sound::play() {
		if (state == PlaybackState::PLAYING)
			return Status::INV_STATE;

		if (state == PlaybackState::STOPPED) {
			if (FAILED(sourceVoice->SubmitSourceBuffer(&audioBuffer)))
				return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to submit source buffer\n"));
		}

		if (FAILED(sourceVoice->Start()))
			return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Unable to start playback\n"));
        state = PlaybackState::PLAYING;
		return Status::OK;
	}
}