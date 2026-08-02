#pragma once

namespace UnitTest::Utils {
    class ObjectGuard {
    private:
        size_t allocatedObjects;

    public:
        ObjectGuard();

        ~ObjectGuard();
    };
}