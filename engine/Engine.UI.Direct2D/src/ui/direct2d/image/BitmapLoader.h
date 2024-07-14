#pragma once

#include "core/image/ImageLoader.h"
#include "ui/direct2d/image/Bitmap.h"
#include "ui/image/BitmapFactory.h"

namespace Ghurund::UI::Direct2D {
    class BitmapLoader:public Loader {
    private:
        Ghurund::Core::ImageLoader& imageLoader;
        IBitmapFactory& bitmapFactory;

    public:
        BitmapLoader(Ghurund::Core::ImageLoader& imageLoader, IBitmapFactory& bitmapFactory):imageLoader(imageLoader), bitmapFactory(bitmapFactory) {}

        virtual Ghurund::UI::Bitmap* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format = ResourceFormat::AUTO,
            LoadOption options = LoadOption::DEFAULT
        ) override {
            IntrusivePointer<Image> image(imageLoader.load(stream, workingDir, format, options));
            return bitmapFactory.makeBitmap(*image.get());
        }

        virtual void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format = ResourceFormat::AUTO,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            Bitmap& bitmap = (Bitmap&)resource;
            imageLoader.save(stream, workingDir, *bitmap.Image, format, options);
        }
    };
}