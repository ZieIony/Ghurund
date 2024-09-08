#include "ghuipch.h"
#include "FontLoader.h"

#include "core/Exceptions.h"

namespace Ghurund::UI {

    Font* FontLoader::load(
        MemoryInputStream& stream,
        const DirectoryPath& workingDir,
        const ResourceFormat& format,
        LoadOption options
    ) {
        Font* font = makeResource<Ghurund::UI::Font>();
        font->init(bitmapFactory, stream.Data, stream.Size);
        return font;
    }

    void FontLoader::save(MemoryOutputStream& stream, const DirectoryPath& workingDir, Resource& resource, const ResourceFormat& format, SaveOption options) const {
        if (format == ResourceFormat::AUTO || format == Font::FORMAT_ATLAS) {
			Font& font = (Font&)resource;
            //if(font.load)
        } else {
            throw FormatNotSupportedException();
        }
    }
}