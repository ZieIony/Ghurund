#include "ghepch.h"
#include "SoundLoader.h"

#include "Sound.h"

namespace Ghurund::Engine {
    void SoundLoader::setupDecompression(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex) {
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

    Ghurund::Engine::SoundLoader::AudioData SoundLoader::readSamples(ComPtr<IMFSourceReader> sourceReader, DWORD streamIndex) {
        uint32_t size = 0;
        List<Buffer> samples;
        ComPtr<IMFSample> sample = nullptr;
        ComPtr<IMFMediaBuffer> buffer = nullptr;

        while (true) {
            DWORD flags = 0;
            if (FAILED(sourceReader->ReadSample(streamIndex, 0, nullptr, &flags, nullptr, sample.GetAddressOf()))) {
                Logger::log(LogType::ERR0R, _T("Unable to read audio sample\n"));
                throw CallFailedException();
            }

            // check whether the data is still valid
            if (flags & MF_SOURCE_READERF_CURRENTMEDIATYPECHANGED)
                break;

            // check for eof
            if (flags & MF_SOURCE_READERF_ENDOFSTREAM)
                break;

            if (sample == nullptr)
                continue;

            // convert data to contiguous buffer
            if (FAILED(sample->ConvertToContiguousBuffer(buffer.GetAddressOf()))) {
                Logger::log(LogType::ERR0R, _T("Unable to convert audio sample to contiguous buffer\n"));
                throw CallFailedException();
            }

            BYTE* localAudioData = nullptr;
            DWORD localAudioDataLength = 0;
            // lock buffer and copy data to local memory
            if (FAILED(buffer->Lock(&localAudioData, nullptr, &localAudioDataLength))) {
                Logger::log(LogType::ERR0R, _T("Critical error: Unable to lock the audio buffer\n"));
                throw CallFailedException();
            }

            Buffer sampleData;
            sampleData.setData(localAudioData, localAudioDataLength);
            samples.add(sampleData);
            size += localAudioDataLength;

            if (FAILED(buffer->Unlock())) {
                Logger::log(LogType::ERR0R, _T("Critical error while unlocking the audio buffer\n"));
                throw CallFailedException();
            }
        }

        uint8_t* audioData = ghnew uint8_t[size];
        uint32_t offset = 0;
        for (auto& sampleData : samples) {
            memcpy(audioData + offset, sampleData.Data, sampleData.Size);
            offset += sampleData.Size;
        }
        return { audioData, size };
    }

    void SoundLoader::loadData(
        Sound& sound,
        MemoryInputStream& stream
    ) {
        ComPtr<IStream> memStream = SHCreateMemStream((const BYTE*)stream.Data, (UINT)stream.Size);
        ComPtr<IMFByteStream> spMFByteStream = nullptr;
        MFCreateMFByteStreamOnStreamEx((IUnknown*)memStream.Get(), &spMFByteStream);

        ComPtr<IMFSourceReader> sourceReader;
        if (FAILED(MFCreateSourceReaderFromByteStream(spMFByteStream.Get(), audio.ReaderConfiguration.Get(), sourceReader.GetAddressOf()))) {
            Logger::log(LogType::ERR0R, _T("Unable to create source reader\n"));
            throw CallFailedException();
        }

        if (FAILED(sourceReader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, false))) {
            Logger::log(LogType::ERR0R, _T("Unable to disable streams\n"));
            throw CallFailedException();
        }

        DWORD streamIndex = (DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM;
        if (FAILED(sourceReader->SetStreamSelection(streamIndex, true))) {
            Logger::log(LogType::ERR0R, _T("Unable to enable first audio stream\n"));
            throw CallFailedException();
        }

        Microsoft::WRL::ComPtr<IMFMediaType> nativeMediaType;
        if (FAILED(sourceReader->GetNativeMediaType(streamIndex, 0, nativeMediaType.GetAddressOf()))) {
            Logger::log(LogType::ERR0R, _T("Unable to query media information\n"));
            throw CallFailedException();
        }

        GUID majorType{};
        HRESULT hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
        if (majorType != MFMediaType_Audio) {
            return Logger::log(LogType::ERR0R, _T("The requested file is not an audio file\n"));
            throw InvalidDataException();
        }

        GUID subType{};
        hr = nativeMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
        if (subType != MFAudioFormat_Float && subType != MFAudioFormat_PCM)
            setupDecompression(sourceReader, streamIndex);

        // uncompress the data and load it into an XAudio2 Buffer
        Microsoft::WRL::ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
        if (FAILED(sourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf()))) {
            Logger::log(LogType::ERR0R, _T("Unable to retrieve the current media type\n"));
            throw CallFailedException();
        }

        WAVEFORMATEX* waveFormat;
        unsigned int waveFormatLength;
        if (FAILED(MFCreateWaveFormatExFromMFMediaType(uncompressedAudioType.Get(), &waveFormat, &waveFormatLength))) {
            Logger::log(LogType::ERR0R, _T("Unable to create the wave format\n"));
            throw CallFailedException();
        }

        if (FAILED(sourceReader->SetStreamSelection(streamIndex, true))) {
            Logger::log(LogType::ERR0R, _T("Unable to select audio stream\n"));
            throw CallFailedException();
        }

        AudioData audioData = readSamples(sourceReader, streamIndex);

        IXAudio2SourceVoice* sourceVoice;
        if (FAILED(audio.Device->CreateSourceVoice(&sourceVoice, waveFormat))) {
            Logger::log(LogType::ERR0R, _T("Unable to create source voice\n"));
            throw CallFailedException();
        }

        XAUDIO2_BUFFER audioBuffer;
        memset(&audioBuffer, 0, sizeof(XAUDIO2_BUFFER));
        audioBuffer.AudioBytes = audioData.size;
        audioBuffer.pAudioData = audioData.data;
        audioBuffer.pContext = nullptr;
        audioBuffer.Flags = XAUDIO2_END_OF_STREAM;
        audioBuffer.LoopCount = XAUDIO2_NO_LOOP_REGION;

        sound.init(*audio.MasteringVoice, sourceVoice, waveFormat, audioBuffer);
    }

    void SoundLoader::loadInternal(
        Sound& resource,
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        loadData(resource, stream);
    }
}
