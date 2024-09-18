#include "ghuidxpch.h"
#include "Bitmap.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI::DirectX {
    const Ghurund::Core::Type& Bitmap::GET_TYPE() {
        static auto PROPERTY_IMAGE = Property<Bitmap, Ghurund::Core::Image*>("Image", &getImage);
        static auto PROPERTY_SIZE = Property<Bitmap, IntSize>("Size", &getSize);

        static const auto CONSTRUCTOR = Constructor<Bitmap>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Bitmap>(Ghurund::UI::NAMESPACE_NAME, "Bitmap")
            .withProperty(PROPERTY_IMAGE)
            .withProperty(PROPERTY_SIZE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Bitmap::finalize() {
        if (image)
            image->release();
    }

    bool Bitmap::isValid() {
        return image && image->Valid && __super::Valid;
    }

    void Bitmap::init(Ghurund::Core::Image& image) {
        setPointer(this->image, &image);
        Valid = true;
    }

    void Bitmap::init(Ghurund::Core::IntSize size, DXGI_FORMAT format) {
        if (image) {
            image->release();
            image = nullptr;
        }

        Valid = true;
    }

    Ghurund::Core::IntSize Bitmap::getSize() const {
        if (!image)
            return { 0,0 };
        return { image->Width, image->Height };
    }
}