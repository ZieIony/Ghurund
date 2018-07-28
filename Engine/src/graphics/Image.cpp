#include "Image.h"
#include <Shlwapi.h>

namespace Ghurund {
    DXGI_FORMAT Image::getDXGIFormatFromWICFormat(WICPixelFormatGUID &wicFormatGUID) {
        if(wicFormatGUID == GUID_WICPixelFormat128bppRGBAFloat) return DXGI_FORMAT_R32G32B32A32_FLOAT;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppRGBAHalf) return DXGI_FORMAT_R16G16B16A16_FLOAT;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppRGBA) return DXGI_FORMAT_R16G16B16A16_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppRGBA) return DXGI_FORMAT_R8G8B8A8_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppBGRA) return DXGI_FORMAT_B8G8R8A8_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppBGR) return DXGI_FORMAT_B8G8R8X8_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102XR) return DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM;

        else if(wicFormatGUID == GUID_WICPixelFormat32bppRGBA1010102) return DXGI_FORMAT_R10G10B10A2_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat16bppBGRA5551) return DXGI_FORMAT_B5G5R5A1_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat16bppBGR565) return DXGI_FORMAT_B5G6R5_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppGrayFloat) return DXGI_FORMAT_R32_FLOAT;
        else if(wicFormatGUID == GUID_WICPixelFormat16bppGrayHalf) return DXGI_FORMAT_R16_FLOAT;
        else if(wicFormatGUID == GUID_WICPixelFormat16bppGray) return DXGI_FORMAT_R16_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat8bppGray) return DXGI_FORMAT_R8_UNORM;
        else if(wicFormatGUID == GUID_WICPixelFormat8bppAlpha) return DXGI_FORMAT_A8_UNORM;

        else return DXGI_FORMAT_UNKNOWN;
    }
    
    WICPixelFormatGUID Image::convertToWICFormat(WICPixelFormatGUID & wicFormatGUID) {
        if(wicFormatGUID == GUID_WICPixelFormatBlackWhite) return GUID_WICPixelFormat8bppGray;
        else if(wicFormatGUID == GUID_WICPixelFormat1bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat2bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat4bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat8bppIndexed) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat2bppGray) return GUID_WICPixelFormat8bppGray;
        else if(wicFormatGUID == GUID_WICPixelFormat4bppGray) return GUID_WICPixelFormat8bppGray;
        else if(wicFormatGUID == GUID_WICPixelFormat16bppGrayFixedPoint) return GUID_WICPixelFormat16bppGrayHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppGrayFixedPoint) return GUID_WICPixelFormat32bppGrayFloat;
        else if(wicFormatGUID == GUID_WICPixelFormat16bppBGR555) return GUID_WICPixelFormat16bppBGRA5551;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppBGR101010) return GUID_WICPixelFormat32bppRGBA1010102;
        else if(wicFormatGUID == GUID_WICPixelFormat24bppBGR) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat24bppRGB) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppPBGRA) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppPRGBA) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat48bppRGB) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat48bppBGR) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppBGRA) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppPRGBA) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppPBGRA) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat48bppRGBFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat48bppBGRFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppRGBAFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppBGRAFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppRGBFixedPoint) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppRGBHalf) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat48bppRGBHalf) return GUID_WICPixelFormat64bppRGBAHalf;
        else if(wicFormatGUID == GUID_WICPixelFormat128bppPRGBAFloat) return GUID_WICPixelFormat128bppRGBAFloat;
        else if(wicFormatGUID == GUID_WICPixelFormat128bppRGBFloat) return GUID_WICPixelFormat128bppRGBAFloat;
        else if(wicFormatGUID == GUID_WICPixelFormat128bppRGBAFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
        else if(wicFormatGUID == GUID_WICPixelFormat128bppRGBFixedPoint) return GUID_WICPixelFormat128bppRGBAFloat;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppRGBE) return GUID_WICPixelFormat128bppRGBAFloat;
        else if(wicFormatGUID == GUID_WICPixelFormat32bppCMYK) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppCMYK) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat40bppCMYKAlpha) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat80bppCMYKAlpha) return GUID_WICPixelFormat64bppRGBA;

#if (_WIN32_WINNT >= _WIN32_WINNT_WIN8) || defined(_WIN7_PLATFORM_UPDATE)
        else if(wicFormatGUID == GUID_WICPixelFormat32bppRGB) return GUID_WICPixelFormat32bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppRGB) return GUID_WICPixelFormat64bppRGBA;
        else if(wicFormatGUID == GUID_WICPixelFormat64bppPRGBAHalf) return GUID_WICPixelFormat64bppRGBAHalf;
#endif

        else return GUID_WICPixelFormatDontCare;
    }
    
    int Image::getDXGIFormatBitsPerPixel(DXGI_FORMAT & dxgiFormat) {
        if(dxgiFormat == DXGI_FORMAT_R32G32B32A32_FLOAT) return 128;
        else if(dxgiFormat == DXGI_FORMAT_R16G16B16A16_FLOAT) return 64;
        else if(dxgiFormat == DXGI_FORMAT_R16G16B16A16_UNORM) return 64;
        else if(dxgiFormat == DXGI_FORMAT_R8G8B8A8_UNORM) return 32;
        else if(dxgiFormat == DXGI_FORMAT_B8G8R8A8_UNORM) return 32;
        else if(dxgiFormat == DXGI_FORMAT_B8G8R8X8_UNORM) return 32;
        else if(dxgiFormat == DXGI_FORMAT_R10G10B10_XR_BIAS_A2_UNORM) return 32;

        else if(dxgiFormat == DXGI_FORMAT_R10G10B10A2_UNORM) return 32;
        else if(dxgiFormat == DXGI_FORMAT_B5G5R5A1_UNORM) return 16;
        else if(dxgiFormat == DXGI_FORMAT_B5G6R5_UNORM) return 16;
        else if(dxgiFormat == DXGI_FORMAT_R32_FLOAT) return 32;
        else if(dxgiFormat == DXGI_FORMAT_R16_FLOAT) return 16;
        else if(dxgiFormat == DXGI_FORMAT_R16_UNORM) return 16;
        else if(dxgiFormat == DXGI_FORMAT_R8_UNORM) return 8;
        else if(dxgiFormat == DXGI_FORMAT_A8_UNORM) return 8;

        return -1;
    }
    
    Status Image::loadInternal(ResourceManager &resourceManager, const void *data, unsigned long size, unsigned long *bytesRead) {
        IWICBitmapDecoder *wicDecoder = nullptr;
        IWICBitmapFrameDecode *wicFrame = nullptr;
        IWICFormatConverter *wicConverter = nullptr;

        bool imageConverted = false;

        ComPtr<IStream> stream = SHCreateMemStream((const BYTE *)data,size);
        if(FAILED(resourceManager.getImageFactory()->CreateDecoderFromStream(stream.Get(),nullptr, WICDecodeMetadataCacheOnLoad, &wicDecoder))) {
            Logger::log(_T("Failed to create decoder for %s\n"), FileName);
            return Status::CALL_FAIL;
        }

        if(FAILED(wicDecoder->GetFrame(0, &wicFrame)))
            return Status::CALL_FAIL;

        WICPixelFormatGUID pixelFormat;
        if(FAILED(wicFrame->GetPixelFormat(&pixelFormat)))
            return Status::CALL_FAIL;

        if(FAILED(wicFrame->GetSize(&width, &height)))
            return Status::CALL_FAIL;

        // TODO: implement sRGB

        dxgiFormat = getDXGIFormatFromWICFormat(pixelFormat);

        if(dxgiFormat == DXGI_FORMAT_UNKNOWN) {
            WICPixelFormatGUID convertToPixelFormat = convertToWICFormat(pixelFormat);

            if(convertToPixelFormat == GUID_WICPixelFormatDontCare)
                return Status::CALL_FAIL;

            dxgiFormat = getDXGIFormatFromWICFormat(convertToPixelFormat);

            if(FAILED(resourceManager.getImageFactory()->CreateFormatConverter(&wicConverter)))
                return Status::CALL_FAIL;

            BOOL canConvert = FALSE;
            if(FAILED(wicConverter->CanConvert(pixelFormat, convertToPixelFormat, &canConvert)) || !canConvert)
                return Status::CALL_FAIL;

            if(FAILED(wicConverter->Initialize(wicFrame, convertToPixelFormat, WICBitmapDitherTypeErrorDiffusion, 0, 0, WICBitmapPaletteTypeCustom)))
                return Status::CALL_FAIL;

            imageConverted = true;
        }

        pixelSize = getDXGIFormatBitsPerPixel(dxgiFormat)/8;
        int bytesPerRow = width * pixelSize;
        int imageSize = bytesPerRow * height;

        imageData = ghnew BYTE[imageSize];

        if(imageConverted) {
            if(FAILED(wicConverter->CopyPixels(0, bytesPerRow, imageSize, imageData)))
                return Status::CALL_FAIL;
        } else {
            if(FAILED(wicFrame->CopyPixels(0, bytesPerRow, imageSize, imageData)))
                return Status::CALL_FAIL;
        }

        return Status::OK;
    }
}