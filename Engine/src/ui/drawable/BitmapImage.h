#pragma once

#include "graphics/Graphics.h"
#include "graphics/Fence.h"
#include "application/log/Logger.h"
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

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<BitmapImage>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(BitmapImage))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    protected:
        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options);
        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options)const;

    public:
        DescriptorHandle descHandle;

        ~BitmapImage() {
            finalize();
        }

        void finalize() {
            if (image != nullptr)
                image->release();
        }

        virtual void invalidate() {
            finalize();
            image = nullptr;
            __super::invalidate();
        }

        virtual bool isValid() {
            return image != nullptr && image->Valid && __super::Valid;
        }

        Status init(ResourceContext& context, Image& image);

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
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)& ResourceFormat::JPG};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;

        static BitmapImage* makeFromImage(ResourceContext& context, const FilePath& imagePath) {
            Ghurund::Image* image = context.ResourceManager.load<Ghurund::Image>(context, imagePath);
            if (image == nullptr)
                return nullptr;
            BitmapImage* texture = ghnew BitmapImage();
            texture->init(context, *image);
            image->release();
            return texture;
        }
    };
}