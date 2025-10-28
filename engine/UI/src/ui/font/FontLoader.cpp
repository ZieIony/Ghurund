#include "ghuipch.h"
#include "FontLoader.h"

namespace Ghurund::UI {

    Resource* FontLoader::loadInternal(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        Font* font = makeResource<Ghurund::UI::Font>();
        font->init(bitmapFactory, stream.Data, stream.Size);
        return font;
    }

    void FontLoader::saveInternal(
        MemoryOutputStream& stream,
        const DirectoryPath& workingDir,
        Resource& resource,
        const ResourceFormat& format,
        SaveOption options
    ) const {
		Font& font = (Font&)resource;
        //if(font.load)
    }
}