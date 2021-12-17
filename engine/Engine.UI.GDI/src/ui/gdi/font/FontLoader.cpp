#include "ghuigdipch.h"
#include "FontLoader.h"

#include "core/Exceptions.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI::GDI {
    Font* FontLoader::load(
        Ghurund::Core::ResourceManager& manager,
        MemoryInputStream& stream,
        const ResourceFormat* format,
        LoadOption options
    ) {
        Font* font = makeResource<Ghurund::UI::GDI::Font>();
        return font;
    }
}