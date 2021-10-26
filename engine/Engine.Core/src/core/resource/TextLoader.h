#pragma once

#include "Loader.h"
#include "TextResource.h"

namespace Ghurund::Core {
    class TextLoader:public Loader {
    public:
        virtual Status load(
            Ghurund::Core::ResourceManager& manager,
            MemoryInputStream& stream,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override {
            TextResource& textResource = (TextResource&)resource;
            textResource.Text = stream.readASCII();
            return Status::OK;
        }

        virtual Status save(
            Ghurund::Core::ResourceManager& manager,
            MemoryOutputStream& stream,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            return Status::NOT_IMPLEMENTED;
        }
    };
}