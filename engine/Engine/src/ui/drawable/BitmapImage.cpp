#include "ghpch.h"
#include "BitmapImage.h"

#include "graphics/Graphics2D.h"

namespace Ghurund::UI {
    const Ghurund::Type& BitmapImage::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<BitmapImage>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(BitmapImage))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void BitmapImage::finalize() {
        if (bitmapImage)
            bitmapImage->Release();
        if (image)
            image->release();
    }

    bool BitmapImage::isValid() {
        return bitmapImage && image && image->Valid && __super::Valid;
    }

    Status BitmapImage::init(Ghurund::Graphics2D& graphics2d, Ghurund::Image& image) {
        setPointer(this->image, &image);

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_NONE,
            D2D1::PixelFormat(image.Format, D2D1_ALPHA_MODE_PREMULTIPLIED)
        );

        if (FAILED(graphics2d.DeviceContext->CreateBitmap(D2D1_SIZE_U{ image.Width, image.Height }, image.Data.Data, image.RowPitch, bitmapProperties, &bitmapImage)))
            return Status::CALL_FAIL;

        Valid = true;

        return Status::OK;
    }

    Status BitmapImage::init(Ghurund::Graphics2D& graphics2d, IntSize size, DXGI_FORMAT format) {
        if (image)
            image->release();

        D2D1_BITMAP_PROPERTIES1 bitmapProperties = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_TARGET,
            D2D1::PixelFormat(format, D2D1_ALPHA_MODE_PREMULTIPLIED)
        );

        if (FAILED(graphics2d.DeviceContext->CreateBitmap(D2D1_SIZE_U{ size.width, size.height }, nullptr, 0, bitmapProperties, &bitmapImage)))
            return Status::CALL_FAIL;

        Valid = true;

        return Status::OK;
    }

    IntSize BitmapImage::getSize() {
        if (!image)
            return { 0,0 };
        return { image->Width, image->Height };
    }
}