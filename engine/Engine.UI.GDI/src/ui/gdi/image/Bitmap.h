#pragma once

#include "core/math/Size.h"
#include "core/image/Image.h"
#include "ui/image/Bitmap.h"

#include <gdiplus.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<Gdiplus::Bitmap>();
}

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class Bitmap:public Ghurund::UI::Bitmap {
    protected:
        static const Array<ResourceFormat>& GET_FORMATS();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Array<ResourceFormat>& FORMATS = GET_FORMATS();

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }

    private:
        Image* image = nullptr;
        Gdiplus::Bitmap* bitmapImage = nullptr;

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

        Status init(Image& image);

        Status init(Ghurund::Core::IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        inline Gdiplus::Bitmap* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) Gdiplus::Bitmap* Data;

        virtual Ghurund::Core::IntSize getSize() const override;
    };
}