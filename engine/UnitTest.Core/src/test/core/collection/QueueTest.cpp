#include "pch.h"
#include "CppUnitTest.h"
#include "TestAllocator.h"
#include "test/MemoryGuard.h"

#include "Common.h"
#include "core/collection/Queue.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace std;

    TEST_CLASS(QueueTest) {
    public:

        TEST_METHOD(Queue_constructor) {
            MemoryGuard guard;
            TestAllocator a;
            {
                Queue<uint32_t, TestAllocator&> queue(a);

                Assert::AreEqual(queue.Size, (size_t)0);
                Assert::AreEqual(queue.Empty, true);
            }
            Assert::AreEqual(a.Allocations, 0);

            {
                Queue<TestClass> queue;

                Assert::AreEqual(queue.Size, (size_t)0);
                Assert::AreEqual(queue.Empty, true);
            }
        }

        TEST_METHOD(Queue_constructorCopy) {
            MemoryGuard guard;
            {
                Queue<uint32_t, TestAllocator> testQueue = { 1, 2, 3 };
                Queue<uint32_t, TestAllocator> queue = Queue<uint32_t, TestAllocator>(testQueue);

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
            }
        }

        TEST_METHOD(Queue_constructorMove) {
            MemoryGuard guard;
            {
                Queue<uint32_t> testQueue = { 1, 2, 3 };
                Queue<uint32_t> queue = std::move(testQueue);

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
            }
        }

        TEST_METHOD(Queue_constructorInitializer) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
            }
        }

        TEST_METHOD(Queue_referenceAssignment) {
            MemoryGuard guard;
            {
                Queue<uint32_t> testQueue = { 1, 2, 3 };
                Queue<uint32_t> queue;
                queue = testQueue;

                Assert::AreEqual(queue.Size, testQueue.Size);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
            }
        }

        TEST_METHOD(Queue_moveAssignment) {
            MemoryGuard guard;
            {
                Queue<uint32_t> testQueue = { 1, 2, 3 };
                Queue<uint32_t> queue;
                queue = std::move(testQueue);

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
            }
        }

        TEST_METHOD(Queue_initializerAssignment) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue;
                queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
            }
        }

        TEST_METHOD(Queue_add) {
            MemoryGuard guard;
            TestAllocator a;
            {
                Queue<uint32_t, TestAllocator&> queue(a);
                queue.add(1);

                Assert::AreEqual(queue.Size, (size_t)1);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(a.Allocations, 1);
                Assert::AreEqual(queue.front(), 1u);
                Assert::AreEqual(queue.back(), 1u);

                queue.add(2);

                Assert::AreEqual(queue.Size, (size_t)2);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(a.Allocations, 2);
                Assert::AreEqual(queue.front(), 1u);
                Assert::AreEqual(queue.back(), 2u);
            }
            Assert::AreEqual(a.Allocations, 0);
        }

        TEST_METHOD(Queue_addAll_initializer) {
            MemoryGuard guard;
            TestAllocator a;
            {
                Queue<uint32_t, TestAllocator&> queue(a);
                queue.addAll({ 1, 2, 3 });

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
                Assert::AreEqual(a.Allocations, 3);
            }
            Assert::AreEqual(a.Allocations, 0);
        }

        TEST_METHOD(Queue_addAll_Queue) {
            MemoryGuard guard;
            TestAllocator a;
            {
                Queue<uint32_t, TestAllocator&> queue(a);
                TestAllocator a2;
                const Queue<uint32_t, TestAllocator&> testQueue = Queue<uint32_t, TestAllocator&>({ 1, 2, 3 }, a2);
                queue.addAll(testQueue);

                Assert::AreEqual(testQueue.Size, (size_t)3);
                Assert::AreEqual(testQueue.Empty, false);
                Assert::AreEqual(testQueue[0], 1u);
                Assert::AreEqual(testQueue[1], 2u);
                Assert::AreEqual(testQueue[2], 3u);

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);

                Assert::AreEqual(queue.Size, testQueue.Size);
                Assert::AreEqual(a.Allocations, 3);
            }
            Assert::AreEqual(a.Allocations, 0);
        }

        TEST_METHOD(Queue_get) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };
                auto val = queue.get(1);

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
                Assert::AreEqual(val, 2u);
            }

            {
                Queue<uint32_t> queue2 = { 1, 2, 3 };
                const uint32_t& val2 = queue2.get(1);
            }
        }

        TEST_METHOD(Queue_arrayOperator) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };
                uint32_t& val = queue[1];

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 1u);
                Assert::AreEqual(queue[1], 2u);
                Assert::AreEqual(queue[2], 3u);
                Assert::AreEqual(val, 2u);

                // does it compile with const?
                const Queue<uint32_t> queue2 = { 1, 2, 3 };
                const uint32_t& val2 = queue2[1];
            }
        }

        TEST_METHOD(Queue_remove) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };
                queue.remove();

                Assert::AreEqual(queue.Size, (size_t)2);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue[0], 2u);
                Assert::AreEqual(queue[1], 3u);
            }
            {
                Queue<uint32_t> queue = { 1 };
                queue.remove();

                Assert::AreEqual(queue.Size, (size_t)0);
                Assert::AreEqual(queue.Empty, true);
            }
        }

        TEST_METHOD(Queue_iterator) {
            MemoryGuard guard;
            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);

                size_t i = 0;
                for (auto& item : queue)
                    Assert::AreEqual(item, testVector[i++]);
            }

            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                const Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);

                size_t i = 0;
                for (auto& item : queue)
                    Assert::AreEqual(item, testVector[i++]);
            }
        }

        TEST_METHOD(Queue_indexOf) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue.indexOf(2), (size_t)1);
                Assert::AreEqual(queue.indexOf(4), (size_t)3);
            }

            {
                const Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::AreEqual(queue.indexOf(2), (size_t)1);
                Assert::AreEqual(queue.indexOf(4), (size_t)3);
            }
        }

        TEST_METHOD(Queue_contains) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::IsTrue(queue.contains(1));
                Assert::IsFalse(queue.contains(4));
            }

            {
                const Queue<uint32_t> queue = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::IsTrue(queue.contains(1));
                Assert::IsFalse(queue.contains(4));
            }
        }

        TEST_METHOD(Queue_comparison) {
            MemoryGuard guard;
            {
                Queue<uint32_t> queue = { 1, 2, 3 };
                Queue<uint32_t> queue2 = { 1, 2, 3 };

                Assert::AreEqual(queue.Size, (size_t)3);
                Assert::AreEqual(queue.Empty, false);
                Assert::IsTrue(queue == queue2);
            }
        }
    };
}
