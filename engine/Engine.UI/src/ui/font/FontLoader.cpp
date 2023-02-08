#include "ghuipch.h"
#include "FontLoader.h"

#include "core/Exceptions.h"
#include "core/logging/Logger.h"
#include "core/image/ImageLoader.h"

namespace Ghurund::UI::GDI {

    Font* FontLoader::load(
        Ghurund::Core::ResourceManager& manager,
        MemoryInputStream& stream,
        const ResourceFormat* format,
        LoadOption options
    ) {
        Font* font = makeResource<Ghurund::UI::Font>();
        font->init(stream.Data, stream.Size);
        return font;
    }
}