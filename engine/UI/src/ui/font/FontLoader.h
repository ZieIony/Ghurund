#pragma once

#include "core/resource/Loader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class FontLoader:public Loader {
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
    };
}