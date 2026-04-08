#pragma once

#include "Font.h"

#include "core/loading/Loader.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class FontLoader:public Loader<Font> {
    protected:
        virtual CoroutineTask<void> loadInternal(
            Font& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override;
    };
}
