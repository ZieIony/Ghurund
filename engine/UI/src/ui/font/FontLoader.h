#pragma once

#include "core/resource/Loader.h"
#include "Font.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class FontLoader:public Loader {
    private:
        IBitmapFactory& bitmapFactory;

    public:
        FontLoader(IBitmapFactory& bitmapFactory):bitmapFactory(bitmapFactory) {}
        virtual Font* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format = ResourceFormat::AUTO,
            LoadOption options = LoadOption::DEFAULT
        ) override;

        virtual void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format = ResourceFormat::AUTO,
            SaveOption options = SaveOption::DEFAULT
        ) const override;
    };
}