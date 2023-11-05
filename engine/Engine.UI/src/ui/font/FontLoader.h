#pragma once

#include "core/resource/Loader.h"
#include "Font.h"
#include "core/Exceptions.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class FontLoader:public Loader {
    public:
        virtual Font* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override;

        virtual void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            throw NotImplementedException();
        }
    };
}