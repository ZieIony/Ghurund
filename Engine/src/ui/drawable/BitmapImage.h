#pragma once

#include "graphics/Graphics.h"
#include "graphics/Fence.h"
#include "graphics/texture/Image.h"

#include <dxgi1_6.h>
#include <d2d1_3.h>

namespace Ghurund::UI {
    using namespace DirectX;
    using Microsoft::WRL::ComPtr;

    class BitmapImage:public Resource {
    private:
        Image* image = nullptr;
        ID2D1Bitmap1* bitmapImage = nullptr;

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<BitmapImage>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(BitmapImage))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        DescriptorHandle descHandle;

        ~BitmapImage() {
            finalize();
        }

        void finalize() {
            if (bitmapImage)
                bitmapImage->Release();
            if (image)
                image->release();
        }

        virtual void invalidate() {
            finalize();
            image = nullptr;
            bitmapImage = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
            return bitmapImage && image && image->Valid && __super::Valid;
        }

        Status init(Ghurund::UI::Graphics2D& graphics2d, Image& image);

        Status init(Ghurund::UI::Graphics2D& graphics2d, IntSize size, DXGI_FORMAT format = DXGI_FORMAT_R8G8B8A8_UNORM);

        inline Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage)) Image* Image;

        inline ID2D1Bitmap1* getData() {
            return bitmapImage;
        }

        __declspec(property(get = getData)) ID2D1Bitmap1* Data;

        inline IntSize getSize() {
            if (!image)
                return { 0,0 };
            return { image->Width, image->Height };
        }

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

        static BitmapImage* makeFromImage(ResourceContext& context, const FilePath& imagePath) {
            Ghurund::Image* image = context.ResourceManager.load<Ghurund::Image>(context, imagePath);
            if (image == nullptr)
                return nullptr;
            BitmapImage* texture = ghnew BitmapImage();
            texture->init(context.Graphics2D, *image);
            image->release();
            return texture;
        }
    };
}