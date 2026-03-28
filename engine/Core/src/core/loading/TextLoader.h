#pragma once

#include "Loader.h"

#include "core/resource/LoadOption.h"
#include "core/resource/TextResource.h"
#include "core/io/MemoryInputStream.h"

namespace Ghurund::Core {
    class TextLoader:public Loader<TextResource> {
    protected:
        virtual void loadInternal(
            TextResource& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            resource.Text = stream.readASCII();
        }
    };
}
