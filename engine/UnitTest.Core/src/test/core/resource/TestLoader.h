#pragma once

#include "core/resource/Loader.h"
#include "TestResource.h"
#include "core/Exceptions.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class TestLoader:public Loader {
    public:
        size_t loadCalls = 0;

        virtual Resource* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format = ResourceFormat::AUTO,
            LoadOption options = LoadOption::DEFAULT
        ) override {
            loadCalls++;
            TestResource* testResource = ghnew TestResource();
            testResource->text = stream.readASCII();
            return testResource;
        }

        virtual void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format = ResourceFormat::AUTO,
            SaveOption options = SaveOption::DEFAULT
        ) const override {
            throw NotImplementedException();
        }
    };
}