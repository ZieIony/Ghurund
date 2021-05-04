#pragma once

#include "core/math/Size.h"
#include "graphics/Graphics2D.h"
#include "graphics/Fence.h"
#include "graphics/buffer/DescriptorHeap.h"
#include "graphics/texture/Image.h"

struct ID2D1Bitmap1;

namespace Ghurund {
    class Image;
}

namespace Ghurund::UI {
    using namespace DirectX;
    using Microsoft::WRL::ComPtr;

    class BitmapImage:public Resource {
    private:
        Image* image = nullptr;
        ID2D1Bitmap1* bitmapImage = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        DescriptorHandle descHandle;

        ~BitmapImage() {
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

        Status init(Ghurund::Graphics2D& graphics2d, Image& image);

        Status init(Ghurund::Graphics2D& graphics2d, IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Image* Image;

        inline ID2D1Bitmap1* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) ID2D1Bitmap1* Data;

        IntSize getSize();

        __declspec(property(get = getSize)) IntSize Size;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static const Array<ResourceFormat*>& getFormats() {
            static const Array<ResourceFormat*> formats = { (ResourceFormat*)&ResourceFormat::JPG , (ResourceFormat*)&ResourceFormat::JPEG , (ResourceFormat*)&ResourceFormat::PNG };
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;

        static BitmapImage* makeFromImage(const FilePath& imagePath);
    };
}