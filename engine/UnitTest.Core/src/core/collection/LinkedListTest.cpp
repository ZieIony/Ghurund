#include "pch.h"
#include "CppUnitTest.h"
#include "TestAllocator.h"
#include "MemoryGuard.h"

#include "core/collection/LinkedList.h"
#include "core/collection/Stack.h"
#include "core/Concepts.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;
    using namespace std;

    struct TestClass {
        uint32_t val = 5;
        const char* text = "text";
    };

    TEST_CLASS(LinkedListTest) {
    public:

        TEST_METHOD(LinkedList_constructor) {
            MemoryGuard guard;
            {
                TestAllocator a;
                LinkedList<uint32_t, TestAllocator&> list(a);

                Assert::AreEqual(list.Size, (size_t)0);
                Assert::AreEqual(list.Empty, true);
                Assert::AreEqual(a.Allocations, 0);
            }

            {
                LinkedList<TestClass> list;

                Assert::AreEqual(list.Size, (size_t)0);
                Assert::AreEqual(list.Empty, true);
            }
        }

        TEST_METHOD(LinkedList_constructorCopy) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t, TestAllocator> testLinkedList = { 1, 2, 3 };
                LinkedList<uint32_t, TestAllocator> list = LinkedList<uint32_t, TestAllocator>(testLinkedList);

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_constructorMove) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> testLinkedList = { 1, 2, 3 };
                LinkedList<uint32_t> list = std::move(testLinkedList);

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_constructorInitializer) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_referenceAssignment) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> testLinkedList = { 1, 2, 3 };
                LinkedList<uint32_t> list;
                list = testLinkedList;

                Assert::AreEqual(list.Size, testLinkedList.Size);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_moveAssignment) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> testLinkedList = { 1, 2, 3 };
                LinkedList<uint32_t> list;
                list = std::move(testLinkedList);

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_initializerAssignment) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list;
                list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_add) {
            MemoryGuard guard;
            TestAllocator a;
            {
                LinkedList<uint32_t, TestAllocator&> list(a);
                list.add(1);

                Assert::AreEqual(list.Size, (size_t)1);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(a.Allocations, 1);
            }
            Assert::AreEqual(a.Allocations, 0);
        }

        TEST_METHOD(LinkedList_addAll_initializer) {
            MemoryGuard guard;
            TestAllocator a;
            {
                LinkedList<uint32_t, TestAllocator&> list(a);
                list.addAll({ 1, 2, 3 });

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
                Assert::AreEqual(a.Allocations, 3);
            }
            Assert::AreEqual(a.Allocations, 0);
        }

        TEST_METHOD(LinkedList_addAll_LinkedList) {
            MemoryGuard guard;
            TestAllocator a;
            {
                LinkedList<uint32_t, TestAllocator&> list(a);
                TestAllocator a2;
                const LinkedList<uint32_t, TestAllocator&> testLinkedList = LinkedList<uint32_t, TestAllocator&>({ 1, 2, 3 }, a2);
                list.addAll(testLinkedList);

                Assert::AreEqual(testLinkedList.Size, (size_t)3);
                Assert::AreEqual(testLinkedList.Empty, false);
                Assert::AreEqual(testLinkedList[0], 1u);
                Assert::AreEqual(testLinkedList[1], 2u);
                Assert::AreEqual(testLinkedList[2], 3u);

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);

                Assert::AreEqual(list.Size, testLinkedList.Size);
                Assert::AreEqual(a.Allocations, 3);
            }
            Assert::AreEqual(a.Allocations, 0);
        }

        TEST_METHOD(LinkedList_insert) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                list.insert(1, 4);

                Assert::AreEqual(list.Size, (size_t)4);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 4u);
                Assert::AreEqual(list[2], 2u);
                Assert::AreEqual(list[3], 3u);
            }
        }

        TEST_METHOD(LinkedList_set) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                list.set(1, 4);

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 4u);
                Assert::AreEqual(list[2], 3u);
            }
        }

        TEST_METHOD(LinkedList_get) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                auto val = list.get(1);

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
                Assert::AreEqual(val, 2u);
            }

            {
                LinkedList<uint32_t> list2 = { 1, 2, 3 };
                const uint32_t& val2 = list2.get(1);
            }
        }

        TEST_METHOD(LinkedList_arrayOperator) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                uint32_t& val = list[1];

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
                Assert::AreEqual(val, 2u);

                // does it compile with const?
                const LinkedList<uint32_t> list2 = { 1, 2, 3 };
                const uint32_t& val2 = list2[1];
            }
        }

        TEST_METHOD(LinkedList_remove) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                list.remove(2);

                Assert::AreEqual(list.Size, (size_t)2);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 3u);
            }
            {
                LinkedList<uint32_t> list = { 1 };
                list.remove(1);

                Assert::AreEqual(list.Size, (size_t)0);
                Assert::AreEqual(list.Empty, true);
            }
        }

        TEST_METHOD(LinkedList_removeAt) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                list.removeAt(2);

                Assert::AreEqual(list.Size, (size_t)2);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
            }
            {
                LinkedList<uint32_t> list = { 1 };
                list.removeAt(0);

                Assert::AreEqual(list.Size, (size_t)0);
                Assert::AreEqual(list.Empty, true);
            }
        }

        TEST_METHOD(LinkedList_removeAll_initializer) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3,4,5,6,7,8 };
                list.removeAll({ 2,4,1 });

                Assert::AreEqual(list.Size, (size_t)5);
                Assert::AreEqual(list.Empty, false);

                LinkedList<uint32_t> testLinkedList = { 3,5,6,7,8 };
                size_t i = 0;
                //for (auto& item : list)
                //    Assert::AreEqual(item, testLinkedList[i++]);
            }
        }
        TEST_METHOD(LinkedList_iterator) {
            MemoryGuard guard;
            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);

                size_t i = 0;
                //for (auto& item : list)
                //    Assert::AreEqual(item, testVector[i++]);
            }

            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                const LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);

                size_t i = 0;
                for (auto& item : list)
                    Assert::AreEqual(item, testVector[i++]);
            }
        }

        TEST_METHOD(LinkedList_indexOf) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list.indexOf(2), (size_t)1);
                Assert::AreEqual(list.indexOf(4), (size_t)3);
            }

            {
                const LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list.indexOf(2), (size_t)1);
                Assert::AreEqual(list.indexOf(4), (size_t)3);
            }
        }

        TEST_METHOD(LinkedList_contains) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::IsTrue(list.contains(1));
                Assert::IsFalse(list.contains(4));
            }

            {
                const LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::IsTrue(list.contains(1));
                Assert::IsFalse(list.contains(4));
            }
        }

        TEST_METHOD(LinkedList_comparison) {
            MemoryGuard guard;
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                LinkedList<uint32_t> list2 = { 1, 2, 3 };

                Assert::AreEqual(list.Size, (size_t)3);
                Assert::AreEqual(list.Empty, false);
                Assert::IsTrue(list == list2);
            }
        }
    };
}
