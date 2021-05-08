#pragma once

#include "core/math/Size.h"
#include "ui/image/Image.h"

#include <d2d1_3.h>

#include "reflection_4bf3b8d2_fe5c_4027_8f30_7830caee3be9.h"

namespace Ghurund::UI {
    using Microsoft::WRL::ComPtr;

    class Bitmap:public Resource {
        reflection_4bf3b8d2_fe5c_4027_8f30_7830caee3be9

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

        Status init(ID2D1DeviceContext5& deviceContext, IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::UI::Image* Image;

        inline ID2D1Bitmap1* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) ID2D1Bitmap1* Data;

        IntSize getSize();

        __declspec(property(get = getSize)) IntSize Size;

        static const Array<ResourceFormat>& getFormats() {
            static const Array<ResourceFormat> formats = {
                ResourceFormat(L"jpg", true, true),
                ResourceFormat(L"jpeg", true, true),
                ResourceFormat(L"png", true, true)
            };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
    };
}