#include "ghuigdipch.h"
#include "Bitmap.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

#include <gdiplus.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<Gdiplus::Bitmap>() {
        static Type TYPE = Type(GH_STRINGIFY(Gdiplus), "Bitmap", sizeof(Gdiplus::Bitmap*));
        return TYPE;
    }
}

namespace Ghurund::UI::GDI {
    const Ghurund::Core::Type& Bitmap::GET_TYPE() {
        static auto PROPERTY_IMAGE = Property<Bitmap, Ghurund::Core::Image*>("Image", &getImage);
        static auto PROPERTY_DATA = Property<Bitmap, Gdiplus::Bitmap*>("Data", &getData);
        static auto PROPERTY_SIZE = Property<Bitmap, IntSize>("Size", &getSize);

        static const auto CONSTRUCTOR = Constructor<Bitmap>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Bitmap>(Ghurund::UI::NAMESPACE_NAME, "Bitmap")
            .withProperty(PROPERTY_IMAGE)
            .withProperty(PROPERTY_DATA)
            .withProperty(PROPERTY_SIZE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Array<ResourceFormat>& Bitmap::GET_FORMATS() {
        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = {
                Ghurund::Core::ResourceFormat(L"jpg", true, true),
                Ghurund::Core::ResourceFormat(L"jpeg", true, true),
                Ghurund::Core::ResourceFormat(L"png", true, true)
        };
        return formats;
    }

    void Bitmap::finalize() {
        if (bitmapImage)
            delete bitmapImage;
        if (image)
            image->release();
    }

    bool Bitmap::isValid() {
        return bitmapImage && image && image->Valid && __super::Valid;
    }

    Status Bitmap::init(Ghurund::Core::Image& image) {
        setPointer(this->image, &image);

        bitmapImage = new Gdiplus::Bitmap(image.Width, image.Height, image.RowPitch, PixelFormat32bppARGB, image.Data.Data);

        Valid = true;

        return Status::OK;
    }

    Status Bitmap::init(Ghurund::Core::IntSize size, DXGI_FORMAT format) {
        if (image) {
            image->release();
            image = nullptr;
        }

        bitmapImage = new Gdiplus::Bitmap(size.width, size.height, PixelFormat32bppARGB);

        Valid = true;

        return Status::OK;
    }

    Ghurund::Core::IntSize Bitmap::getSize() const {
        if (!image)
            return { 0,0 };
        return { image->Width, image->Height };
    }
}