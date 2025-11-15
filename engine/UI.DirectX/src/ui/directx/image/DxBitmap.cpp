#include "ghuidxpch.h"
#include "DxBitmap.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI::DirectX {
    const Ghurund::Core::Type& DxBitmap::GET_TYPE() {
        static auto PROPERTY_IMAGE = Property<DxBitmap, Ghurund::Core::Image*>("Image", &getImage);
        static auto PROPERTY_SIZE = Property<DxBitmap, IntSize>("Size", &getSize);

        static const Ghurund::Core::Type TYPE = TypeBuilder<DxBitmap>()
            .withProperty(PROPERTY_IMAGE)
            .withProperty(PROPERTY_SIZE)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DxBitmap::finalize() {
        if (image)
            image->release();
    }

    bool DxBitmap::isValid() {
        return image && image->Valid && __super::Valid;
    }

    void DxBitmap::init(Ghurund::Core::Image& image) {
        setPointer(this->image, &image);
    }

    void DxBitmap::init(Ghurund::Core::IntSize size, DXGI_FORMAT format) {
        if (image) {
            image->release();
            image = nullptr;
        }
    }

    Ghurund::Core::IntSize DxBitmap::getSize() const {
        if (!image)
            return { 0,0 };
        return { image->Width, image->Height };
    }
}