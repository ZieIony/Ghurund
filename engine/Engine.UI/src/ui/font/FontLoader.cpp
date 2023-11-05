#include "ghuipch.h"
#include "FontLoader.h"

#include "core/Exceptions.h"
#include "core/logging/Logger.h"
#include "core/image/ImageLoader.h"

namespace Ghurund::UI {

    Font* FontLoader::load(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat* format,
        LoadOption options
    ) {
        Font* font = makeResource<Ghurund::UI::Font>();
        font->init(stream.Data, stream.Size);
        return font;
    }
}