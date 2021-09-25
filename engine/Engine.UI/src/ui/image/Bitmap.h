#pragma once

#include "core/math/Size.h"
#include "ui/image/Image.h"

#include <d2d1_3.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<ID2D1Bitmap1>();
}

namespace Ghurund::UI {
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::Core;

    class Bitmap:public Ghurund::Core::Resource {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {

            return TYPE;
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

        __declspec(property(get = getImage)) Ghurund::UI::Image* Image;

        inline ID2D1Bitmap1* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) ID2D1Bitmap1* Data;

        Ghurund::Core::IntSize getSize();

        __declspec(property(get = getSize)) Ghurund::Core::IntSize Size;

        static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() {
            static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat> formats = {
                Ghurund::Core::ResourceFormat(L"jpg", true, true),
                Ghurund::Core::ResourceFormat(L"jpeg", true, true),
                Ghurund::Core::ResourceFormat(L"png", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& Formats;
    };
}