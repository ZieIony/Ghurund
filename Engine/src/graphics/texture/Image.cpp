#include "Image.h"
#include "resource/ResourceContext.h"

#include <Shlwapi.h>

namespace Ghurund {
    DXGI_FORMAT Image::getDXGIFormatFromWICFormat(WICPixelFormatGUID& wicFormatGUID) const {
        if (wicFormatGUID == GUID_WICPixelFormat128bppRGBAFloat) return DXGI_FORMAT_R32G32B32A32_FLOAT;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBAHalf) return DXGI_FORMAT_R16G16B16A16_FLOAT;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBA) return DXGI_FORMAT_R16G16B16A16_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBA) return DXGI_FORMAT_R8G8B8A8_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppBGRA) return DXGI_FORMAT_B8G8R8A8_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppBGR) return DXGI_FORMAT_B8G8R8X8_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102XR) return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

        else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102) return DXGI_FORMAT_R10G10B10A2_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat16bppBGRA5551) return DXGI_FORMAT_B5G5R5A1_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat16bppBGR565) return DXGI_FORMAT_B5G6R5_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppGrayFloat) return DXGI_FORMAT_R32_FLOAT;
        else if (wicFormatGUID == GUID_WICPixelFormat16bppGrayHalf) return DXGI_FORMAT_R16_FLOAT;
        else if (wicFormatGUID == GUID_WICPixelFormat16bppGray) return DXGI_FORMAT_R16_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat8bppGray) return DXGI_FORMAT_R8_UNORM;
        else if (wicFormatGUID == GUID_WICPixelFormat8bppAlpha) return DXGI_FORMAT_A8_UNORM;

        else return DXGI_FORMAT_UNKNOWN;
    }

    WICPixelFormatGUID Image::getWICFormatFromDXGIFormat(DXGI_FORMAT format, bool* sRGB) const {
        WICPixelFormatGUID pfGuid;
        switch (format) {
        case DXGI_FORMAT_R32G32B32A32_FLOAT:            pfGuid = GUID_WICPixelFormat128bppRGBAFloat; break;
        case DXGI_FORMAT_R16G16B16A16_FLOAT:            pfGuid = GUID_WICPixelFormat64bppRGBAHalf; break;
        case DXGI_FORMAT_R16G16B16A16_UNORM:            pfGuid = GUID_WICPixelFormat64bppRGBA; break;
        case DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM:    pfGuid = GUID_WICPixelFormat32bppRGBA1010102XR; break;
        case DXGI_FORMAT_R10G10B10A2_UNORM:             pfGuid = GUID_WICPixelFormat32bppRGBA1010102; break;
        case DXGI_FORMAT_B5G5R5A1_UNORM:                pfGuid = GUID_WICPixelFormat16bppBGRA5551; break;
        case DXGI_FORMAT_B5G6R5_UNORM:                  pfGuid = GUID_WICPixelFormat16bppBGR565; break;
        case DXGI_FORMAT_R32_FLOAT:                     pfGuid = GUID_WICPixelFormat32bppGrayFloat; break;
        case DXGI_FORMAT_R16_FLOAT:                     pfGuid = GUID_WICPixelFormat16bppGrayHalf; break;
        case DXGI_FORMAT_R16_UNORM:                     pfGuid = GUID_WICPixelFormat16bppGray; break;
        case DXGI_FORMAT_R8_UNORM:                      pfGuid = GUID_WICPixelFormat8bppGray; break;
        case DXGI_FORMAT_A8_UNORM:                      pfGuid = GUID_WICPixelFormat8bppAlpha; break;

        case DXGI_FORMAT_R8G8B8A8_UNORM:
            pfGuid = GUID_WICPixelFormat32bppRGBA;
            break;

        case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
            pfGuid = GUID_WICPixelFormat32bppRGBA;
            if (sRGB)
                * sRGB = true;
            break;

        case DXGI_FORMAT_B8G8R8A8_UNORM:
            pfGuid = GUID_WICPixelFormat32bppBGRA;
            break;

        case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
            pfGuid = GUID_WICPixelFormat32bppBGRA;
            if (sRGB)
                * sRGB = true;
            break;

        case DXGI_FORMAT_B8G8R8X8_UNORM:
            pfGuid = GUID_WICPixelFormat32bppBGR;
            break;

        case DXGI_FORMAT_B8G8R8X8_UNORM_SRGB:
            pfGuid = GUID_WICPixelFormat32bppBGR;
            if (sRGB)
                * sRGB = true;
            break;

        default:
            return GUID_WICPixelFormatUndefined;
        }

        return pfGuid;
    }

    WICPixelFormatGUID Image::convertToWICFormat(WICPixelFormatGUID & wicFormatGUID) const {
        if (wicFormatGUID == GUID_WICPixelFormatBlackWhite) return GUID_WICPixelFormat8bppGray;
        else if (wicFormatGUID == GUID_WICPixelFormat1bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat2bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat4bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat8bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat2bppGray) return GUID_WICPixelFormat8bppGray;
        else if (wicFormatGUID == GUID_WICPixelFormat4bppGray) return GUID_WICPixelFormat8bppGray;
        else if (wicFormatGUID == GUID_WICPixelFormat16bppGrayFixedPoint) return GUID_WICPixelFormat16bppGrayHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppGrayFixedPoint) return GUID_WICPixelFormat32bppGrayFloat;
        else if (wicFormatGUID == GUID_WICPixelFormat16bppBGR555) return GUID_WICPixelFormat16bppBGRA5551;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppBGR101010) return GUID_WICPixelFormat32bppRGBA1010102;
        else if (wicFormatGUID == GUID_WICPixelFormat24bppBGR) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat24bppRGB) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppPBGRA) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppPRGBA) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat48bppRGB) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat48bppBGR) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppBGRA) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppPRGBA) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppPBGRA) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat48bppRGBFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat48bppBGRFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBAFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppBGRAFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppRGBHalf) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat48bppRGBHalf) return GUID_WICPixelFormat64bppRGBAHalf;
        else if (wicFormatGUID == GUID_WICPixelFormat128bppPRGBAFloat) return GUID_WICPixelFormat128bppRGBAFloat;
        else if (wicFormatGUID == GUID_WICPixelFormat128bppRGBFloat) return GUID_WICPixelFormat128bppRGBAFloat;
        else if (wicFormatGUID == GUID_WICPixelFormat128bppRGBAFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
        else if (wicFormatGUID == GUID_WICPixelFormat128bppRGBFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppRGBE) return GUID_WICPixelFormat128bppRGBAFloat;
        else if (wicFormatGUID == GUID_WICPixelFormat32bppCMYK) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppCMYK) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat40bppCMYKAlpha) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat80bppCMYKAlpha) return GUID_WICPixelFormat64bppRGBA;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
        else if (wicFormatGUID == GUID_WICPixelFormat32bppRGB) return GUID_WICPixelFormat32bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppRGB) return GUID_WICPixelFormat64bppRGBA;
        else if (wicFormatGUID == GUID_WICPixelFormat64bppPRGBAHalf) return GUID_WICPixelFormat64bppRGBAHalf;
#endif

        else return GUID_WICPixelFormatDontCare;
    }

    int Image::getDXGIFormatBitsPerPixel(DXGI_FORMAT & dxgiFormat) {
        if (dxgiFormat == DXGI_FORMAT_R32G32B32A32_FLOAT) return 128;
        else if (dxgiFormat == DXGI_FORMAT_R16G16B16A16_FLOAT) return 64;
        else if (dxgiFormat == DXGI_FORMAT_R16G16B16A16_UNORM) return 64;
        else if (dxgiFormat == DXGI_FORMAT_R8G8B8A8_UNORM) return 32;
        else if (dxgiFormat == DXGI_FORMAT_B8G8R8A8_UNORM) return 32;
        else if (dxgiFormat == DXGI_FORMAT_B8G8R8X8_UNORM) return 32;
        else if (dxgiFormat == DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM) return 32;

        else if (dxgiFormat == DXGI_FORMAT_R10G10B10A2_UNORM) return 32;
        else if (dxgiFormat == DXGI_FORMAT_B5G5R5A1_UNORM) return 16;
        else if (dxgiFormat == DXGI_FORMAT_B5G6R5_UNORM) return 16;
        else if (dxgiFormat == DXGI_FORMAT_R32_FLOAT) return 32;
        else if (dxgiFormat == DXGI_FORMAT_R16_FLOAT) return 16;
        else if (dxgiFormat == DXGI_FORMAT_R16_UNORM) return 16;
        else if (dxgiFormat == DXGI_FORMAT_R8_UNORM) return 8;
        else if (dxgiFormat == DXGI_FORMAT_A8_UNORM) return 8;

        return -1;
    }

    Status Image::loadInternal(ResourceContext & context, const DirectoryPath & workingDir, MemoryInputStream & stream, LoadOption options) {
        IWICBitmapDecoder* wicDecoder = nullptr;
        IWICBitmapFrameDecode* wicFrame = nullptr;
        IWICFormatConverter* wicConverter = nullptr;

        bool imageConverted = false;

        ComPtr<IStream> memStream = SHCreateMemStream((const BYTE*)stream.Data, stream.Size);
        if (FAILED(context.ImageFactory->CreateDecoderFromStream(memStream.Get(), nullptr, WICDecodeMetadataCacheOnLoad, &wicDecoder)))
            return Logger::log(LogType::ERR0R, Status::CALL_FAIL, _T("Failed to create decoder\n"));

        if (FAILED(wicDecoder->GetFrame(0, &wicFrame)))
            return Status::CALL_FAIL;

        WICPixelFormatGUID pixelFormat;
        if (FAILED(wicFrame->GetPixelFormat(&pixelFormat)))
            return Status::CALL_FAIL;

        if (FAILED(wicFrame->GetSize(&width, &height)))
            return Status::CALL_FAIL;

        // TODO: implement sRGB

        format = getDXGIFormatFromWICFormat(pixelFormat);

        if (format == DXGI_FORMAT_UNKNOWN) {
            WICPixelFormatGUID convertToPixelFormat = convertToWICFormat(pixelFormat);

            if (convertToPixelFormat == GUID_WICPixelFormatDontCare)
                return Status::CALL_FAIL;

            format = getDXGIFormatFromWICFormat(convertToPixelFormat);

            if (FAILED(context.ImageFactory->CreateFormatConverter(&wicConverter)))
                return Status::CALL_FAIL;

            BOOL canConvert = FALSE;
            if (FAILED(wicConverter->CanConvert(pixelFormat, convertToPixelFormat, &canConvert)) || !canConvert)
                return Status::CALL_FAIL;

            if (FAILED(wicConverter->Initialize(wicFrame, convertToPixelFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom)))
                return Status::CALL_FAIL;

            imageConverted = true;
        }

        pixelSize = getDXGIFormatBitsPerPixel(format) / 8;
        rowPitch = width * pixelSize;
        int imageSize = rowPitch * height;

        imageData = ghnew Buffer(imageSize);

        if (imageConverted) {
            if (FAILED(wicConverter->CopyPixels(0, rowPitch, imageSize, imageData->Data)))
                return Status::CALL_FAIL;
        } else {
            if (FAILED(wicFrame->CopyPixels(0, rowPitch, imageSize, imageData->Data)))
                return Status::CALL_FAIL;
        }

        return Status::OK;
    }

    Status Image::saveInternal(ResourceContext & context, const DirectoryPath & workingDir, MemoryOutputStream & stream, SaveOption options) const {
        IWICImagingFactory* pWIC = context.ImageFactory;
        GUID guidContainerFormat = options & SaveOption::FORMAT_PNG ? GUID_ContainerFormatPng : GUID_ContainerFormatJpeg;

        UINT64 dstRowPitch = imageData->Size / height;// (fpRowPitch + 255) & ~0xFF;

        bool sRGB = false;
        WICPixelFormatGUID pfGuid = getWICFormatFromDXGIFormat(format, &sRGB);

        ComPtr<IWICStream> wicStream;
        HRESULT hr = pWIC->CreateStream(wicStream.GetAddressOf());
        if (FAILED(hr))
            return Status::CALL_FAIL;

        ComPtr<IStream> memStream = SHCreateMemStream(nullptr, 0);
        hr = wicStream->InitializeFromIStream(memStream.Get());
        if (FAILED(hr))
            return Status::CALL_FAIL;

        ComPtr<IWICBitmapEncoder> encoder;
        hr = pWIC->CreateEncoder(guidContainerFormat, nullptr, encoder.GetAddressOf());
        if (FAILED(hr))
            return Status::CALL_FAIL;

        hr = encoder->Initialize(wicStream.Get(), WICBitmapEncoderNoCache);
        if (FAILED(hr))
            return Status::CALL_FAIL;

        ComPtr<IWICBitmapFrameEncode> frame;
        ComPtr<IPropertyBag2> props;
        hr = encoder->CreateNewFrame(frame.GetAddressOf(), props.GetAddressOf());
        if (FAILED(hr))
            return Status::CALL_FAIL;

        hr = frame->Initialize(props.Get());
        if (FAILED(hr))
            return Status::CALL_FAIL;

        hr = frame->SetSize(width, height);
        if (FAILED(hr))
            return Status::CALL_FAIL;

        hr = frame->SetResolution(72, 72);
        if (FAILED(hr))
            return Status::CALL_FAIL;

        WICPixelFormatGUID targetGuid;
        // Screenshots don't typically include the alpha channel of the render target
        switch (format) {
        case DXGI_FORMAT_R32G32B32A32_FLOAT:
        case DXGI_FORMAT_R16G16B16A16_FLOAT:
            targetGuid = GUID_WICPixelFormat96bppRGBFloat; // WIC 2
            break;

        case DXGI_FORMAT_R16G16B16A16_UNORM: targetGuid = GUID_WICPixelFormat48bppBGR; break;
        case DXGI_FORMAT_B5G5R5A1_UNORM:     targetGuid = GUID_WICPixelFormat16bppBGR555; break;
        case DXGI_FORMAT_B5G6R5_UNORM:       targetGuid = GUID_WICPixelFormat16bppBGR565; break;

        case DXGI_FORMAT_R32_FLOAT:
        case DXGI_FORMAT_R16_FLOAT:
        case DXGI_FORMAT_R16_UNORM:
        case DXGI_FORMAT_R8_UNORM:
        case DXGI_FORMAT_A8_UNORM:
            targetGuid = GUID_WICPixelFormat8bppGray;
            break;

        default:
            targetGuid = GUID_WICPixelFormat24bppBGR;
            break;
        }

        hr = frame->SetPixelFormat(&targetGuid);
        if (FAILED(hr))
            return Status::CALL_FAIL;

        if (memcmp(&targetGuid, &pfGuid, sizeof(WICPixelFormatGUID)) != 0) {
            // Conversion required to write
            ComPtr<IWICBitmap> source;
            hr = pWIC->CreateBitmapFromMemory(width, height, pfGuid,
                static_cast<UINT>(dstRowPitch), imageData->Size,
                imageData->Data, source.GetAddressOf());
            if (FAILED(hr)) {
                return Status::CALL_FAIL;
            }

            ComPtr<IWICFormatConverter> FC;
            hr = pWIC->CreateFormatConverter(FC.GetAddressOf());
            if (FAILED(hr)) {
                return Status::CALL_FAIL;
            }

            BOOL canConvert = FALSE;
            hr = FC->CanConvert(pfGuid, targetGuid, &canConvert);
            if (FAILED(hr) || !canConvert) {
                //return E_UNEXPECTED;
            }

            hr = FC->Initialize(source.Get(), targetGuid, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeMedianCut);
            if (FAILED(hr)) {
                return Status::CALL_FAIL;
            }

            WICRect rect = {0, 0, (int)width, (int)height};
            hr = frame->WriteSource(FC.Get(), &rect);
            if (FAILED(hr)) {
                return Status::CALL_FAIL;
            }
        } else {
            hr = frame->WritePixels(height, static_cast<UINT>(dstRowPitch), imageData->Size, imageData->Data);
            if (FAILED(hr))
                return Status::CALL_FAIL;
        }

        hr = frame->Commit();
        if (FAILED(hr))
            return Status::CALL_FAIL;

        hr = encoder->Commit();
        if (FAILED(hr))
            return Status::CALL_FAIL;

        STATSTG stg = {0};
        LARGE_INTEGER dlibMove = {0};

        hr = memStream->Seek(dlibMove, STREAM_SEEK_SET, NULL);
        hr = memStream->Stat(&stg, STATFLAG_NONAME);
        BYTE* data = ghnew BYTE[stg.cbSize.LowPart];
        memStream->Read(data, stg.cbSize.LowPart, nullptr);
        stream.writeBytes(data, stg.cbSize.LowPart);
        delete[] data;

        return Status::OK;
    }
}