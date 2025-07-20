#pragma once

#include "Loader.h"
#include "TextResource.h"
#include "core/exception/Exceptions.h"

namespace Ghurund::Core {
    class TextLoader:public Loader {
    protected:
        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) {
            TextResource* textResource = ghnew TextResource();
            textResource->Text = stream.readASCII();
            return textResource;
        }
    };
}