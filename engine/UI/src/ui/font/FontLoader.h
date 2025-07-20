#pragma once

#include "core/resource/Loader.h"
#include "Font.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class FontLoader:public Loader {
    private:
        IBitmapFactory& bitmapFactory;

    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const override;

    public:
        FontLoader(IBitmapFactory& bitmapFactory):bitmapFactory(bitmapFactory) {}
    };
}