#pragma once

#include "core/math/Size.h"
#include "core/image/Image.h"
#include "ui/image/Bitmap.h"

#include <d2d1_3.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID2D1Bitmap1>();
}

namespace Ghurund::UI::Direct2D {
    using namespace Ghurund::Core;

    class Bitmap:public Ghurund::UI::Bitmap {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        static const Array<ResourceFormat>& GET_FORMATS();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        inline static const Array<ResourceFormat>& FORMATS = GET_FORMATS();

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }

    private:
        Image* image = nullptr;
        ID2D1Bitmap1* bitmapImage = nullptr;

    public:
        ~Bitmap() {
            finalize();
        }

        void finalize();

        virtual void invalidate() {
            finalize();
            image = nullptr;
            bitmapImage = nullptr;
            __super::invalidate();
        }

        virtual bool isValid();

        Status init(ID2D1DeviceContext5& deviceContext, Image& image);

        Status init(ID2D1DeviceContext5& deviceContext, Ghurund::Core::IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        inline ID2D1Bitmap1* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) ID2D1Bitmap1* Data;

        virtual Ghurund::Core::IntSize getSize() const override;
    };
}