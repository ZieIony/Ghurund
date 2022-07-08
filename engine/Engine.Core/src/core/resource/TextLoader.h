#pragma once

#include "Loader.h"
#include "TextResource.h"
#include "core/Exceptions.h"

namespace Ghurund::Core {
    class TextLoader:public Loader {
    public:
        virtual Resource* load(
            Ghurund::Core::ResourceManager& manager,
            MemoryInputStream& stream,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override {
            TextResource* textResource = ghnew TextResource();
            textResource->Text = stream.readASCII();
            return textResource;
        }

        virtual void save(
            const Ghurund::Core::ResourceManager& manager,
            MemoryOutputStream& stream,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            throw NotImplementedException();
        }
    };
}