#pragma once

#include "Bitmap.h"
#include "core/image/ImageLoader.h"

namespace Ghurund::UI::OpenGL {
    class BitmapLoader:public Loader {
    private:
        Ghurund::Core::ImageLoader& imageLoader;

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            SharedPointer<Bitmap> bitmap(ghnew Bitmap());
            SharedPointer<Image> image((Image*)imageLoader.load(stream, workingDir, format, options));
            bitmap->init(*image.get());
            bitmap->addReference();
            return bitmap.get();
        }

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override {
            Bitmap& bitmap = (Bitmap&)resource;
            imageLoader.save(stream, workingDir, *bitmap.Image, format, options);
        }

    public:
        BitmapLoader(Ghurund::Core::ImageLoader& imageLoader):imageLoader(imageLoader) {}
    };
}