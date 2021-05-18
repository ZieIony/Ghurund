#pragma once

#include "Bitmap.h"
#include "ui/image/ImageLoader.h"

namespace Ghurund::UI {
    class BitmapLoader:public Loader {
        ImageLoader& imageLoader;
        ID2D1DeviceContext5& deviceContext;

    public:
        BitmapLoader(ImageLoader& imageLoader, ID2D1DeviceContext5& deviceContext):imageLoader(imageLoader), deviceContext(deviceContext) {}

        virtual Status load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, LoadOption options = LoadOption::DEFAULT) override {
            Bitmap& bitmap = (Bitmap&)resource;
            Image* image = ghnew Image();
            Status result = imageLoader.load(manager, stream, *image, format, options);
            if (result == Status::OK)
                bitmap.init(deviceContext, *image);
            image->release();
            return result;
        }

        virtual Status save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const override {
            Bitmap& bitmap = (Bitmap&)resource;
            return imageLoader.save(manager, stream, *bitmap.Image, format, options);
        }
    };
}