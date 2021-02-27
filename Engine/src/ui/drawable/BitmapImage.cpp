#include "BitmapImage.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/Graphics2D.h"
#include "resource/ResourceContext.h"

namespace Ghurund::UI {
    Status BitmapImage::loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        Status result;
        if (image)
            image->release();
        image = ghnew Ghurund::Image();
        result = image->load(context, workingDir, stream, options);
        if (filterStatus(result, options) != Status::OK) {
            image->release();
            return result;
        }
        return init(context.Graphics2D, *image);
    }

    Status BitmapImage::saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
        return image->save(context, workingDir, stream, options);
    }

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

    Status BitmapImage::init(Ghurund::UI::Graphics2D& graphics2d, Ghurund::Image& image) {
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

    Status BitmapImage::init(Ghurund::UI::Graphics2D& graphics2d, IntSize size, DXGI_FORMAT format) {
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
    
    BitmapImage* BitmapImage::makeFromImage(ResourceContext& context, const FilePath& imagePath) {
        Ghurund::Image* image = context.ResourceManager.load<Ghurund::Image>(context, imagePath);
        if (image == nullptr)
            return nullptr;
        BitmapImage* texture = ghnew BitmapImage();
        texture->init(context.Graphics2D, *image);
        image->release();
        return texture;
    }
}