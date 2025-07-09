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
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Bitmap::GET_TYPE();
#pragma endregion

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

        void init(NotNull<ID2D1DeviceContext5> deviceContext, Image& image);

        void init(NotNull<ID2D1DeviceContext5> deviceContext, Ghurund::Core::IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        inline ID2D1Bitmap1* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) ID2D1Bitmap1* Data;

        virtual Ghurund::Core::IntSize getSize() const override;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Bitmap::FORMATS;
        }

    public:
        static const inline Ghurund::Core::ResourceFormat FORMAT_JPG = Ghurund::Core::ResourceFormat(L"jpg", true, true);
        static const inline Ghurund::Core::ResourceFormat FORMAT_JPEG = Ghurund::Core::ResourceFormat(L"jpeg", true, true);
        static const inline Ghurund::Core::ResourceFormat FORMAT_PNG = Ghurund::Core::ResourceFormat(L"png", true, true);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };
#pragma endregion
    };
}