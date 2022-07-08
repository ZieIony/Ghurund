#pragma once

#include "core/resource/Loader.h"
#include "Font.h"
#include "core/Exceptions.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class FontLoader:public Loader {
    public:
        virtual Font* load(
            Ghurund::Core::ResourceManager& manager,
            MemoryInputStream& stream,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) override;

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