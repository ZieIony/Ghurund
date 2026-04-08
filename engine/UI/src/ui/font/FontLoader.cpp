#include "ghuipch.h"
#include "FontLoader.h"

#include "Font.h"

namespace Ghurund::UI {

    CoroutineTask<void> FontLoader::loadInternal(
        Font& resource,
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        resource.init(stream.Data, stream.Size);
        co_return;
    }
}
