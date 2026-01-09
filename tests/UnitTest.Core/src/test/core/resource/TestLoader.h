#pragma once

#include "TestResource.h"

#include "core/loading/Loader.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class TestLoader:public Loader {
    public:
        size_t loadCalls = 0;

        virtual Resource* loadInternal(
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
    };
}