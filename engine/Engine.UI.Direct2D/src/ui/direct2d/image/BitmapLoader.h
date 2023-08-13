#pragma once

#include "Bitmap.h"
#include "core/image/ImageLoader.h"

namespace Ghurund::UI::Direct2D {
    class BitmapLoader:public Loader {
        Ghurund::Core::ImageLoader& imageLoader;
        ID2D1DeviceContext5& deviceContext;

    public:
        BitmapLoader(Ghurund::Core::ImageLoader& imageLoader, ID2D1DeviceContext5& deviceContext):imageLoader(imageLoader), deviceContext(deviceContext) {}

        virtual Bitmap* load(
            ResourceManager& manager,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override {
            SharedPointer<Bitmap> bitmap(ghnew Bitmap());
            SharedPointer<Image> image(imageLoader.load(manager, stream, workingDir, format, options));
            bitmap->init(deviceContext, *image.get());
            bitmap->addReference();
            return bitmap.get();
        }

        virtual void save(
            const ResourceManager& manager,
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            Bitmap& bitmap = (Bitmap&)resource;
            imageLoader.save(manager, stream, workingDir, *bitmap.Image, format, options);
        }
    };
}