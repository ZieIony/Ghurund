#pragma once

#include "core/math/Size.h"
#include "core/image/Image.h"
#include "ui/image/Bitmap.h"

namespace Ghurund::UI::DirectX {
    using namespace Ghurund::Core;

    class DxBitmap:public Ghurund::UI::Bitmap {
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

    public:
        ~DxBitmap() {
            finalize();
        }

        void finalize();

        virtual void invalidate() {
            finalize();
            image = nullptr;
            __super::invalidate();
        }

        virtual bool isValid();

        void init(Image& image);

        void init(Ghurund::Core::IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Ghurund::Core::Image* Image;

        virtual Ghurund::Core::IntSize getSize() const override;

#pragma region formats
    protected:
        virtual const Array<ResourceFormat>& getFormatsImpl() const override {
            return Bitmap::FORMATS;
        }

    public:
        static const inline ResourceFormat FORMAT_JPG = ResourceFormat(L"jpg", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_JPEG = ResourceFormat(L"jpeg", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
        static const inline ResourceFormat FORMAT_PNG = ResourceFormat(L"png", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_JPG, FORMAT_JPEG, FORMAT_PNG };
#pragma endregion
    };
}