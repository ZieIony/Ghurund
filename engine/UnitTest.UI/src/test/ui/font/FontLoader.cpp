#include "pch.h"
#include "FontLoader.h"

namespace UnitTest {
    Font* FontLoader::load(
        Ghurund::Core::ResourceManager& manager,
        MemoryInputStream& stream,
        const ResourceFormat* format,
        LoadOption options
    ) {
        return makeResource<UnitTest::Font>();
    }
}