#pragma once

#include "TestResource.h"

#include "core/loading/Loader.h"

namespace UnitTest {
    using namespace Ghurund::Core;

    class TestLoader:public Loader<TestResource> {
    public:
        size_t loadCalls = 0;

        virtual void loadInternal(
            TestResource& resource,
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) override {
            loadCalls++;
            resource.text = stream.readASCII();
        }
    };
}
