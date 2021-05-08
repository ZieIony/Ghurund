#include "ghuipch.h"
#include "Bitmap.h"

#include <d2d1_3.h>

namespace Ghurund::UI {
    void Bitmap::finalize() {
        if (bitmapImage)
            bitmapImage->Release();
        if (image)
            image->release();
    }

    bool Bitmap::isValid() {
        return bitmapImage && image && image->Valid && __super::Valid;
    }

    Status Bitmap::init(ID2D1DeviceContext5& deviceContext, Ghurund::UI::Image& image) {
        setPointer(this->image, &image);

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_NONE,
            D2D1::PixelFormat(image.Format, D2D1_ALPHA_MODE_PREMULTIPLIED)
        );

        if (FAILED(deviceContext.CreateBitmap(D2D1_SIZE_U{ image.Width, image.Height }, image.Data.Data, image.RowPitch, bitmapProperties, &bitmapImage)))
            return Status::CALL_FAIL;

        Valid = true;

        return Status::OK;
    }

    Status Bitmap::init(ID2D1DeviceContext5& deviceContext, IntSize size, DXGI_FORMAT format) {
        if (image)
            image->release();

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET,
            D2D1::PixelFormat(format, D2D1_ALPHA_MODE_PREMULTIPLIED)
        );

        if (FAILED(deviceContext.CreateBitmap(D2D1_SIZE_U{ size.width, size.height }, nullptr, 0, bitmapProperties, &bitmapImage)))
            return Status::CALL_FAIL;

        Valid = true;

        return Status::OK;
    }

    IntSize Bitmap::getSize() {
        if (!image)
            return { 0,0 };
        return { image->Width, image->Height };
    }
}