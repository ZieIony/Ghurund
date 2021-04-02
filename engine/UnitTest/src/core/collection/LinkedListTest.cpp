#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/LinkedList.h"
#include "core/collection/Stack.h"
#include "TestAllocator.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;
    using namespace std;

    struct TestClass {
        uint32_t val = 5;
        const char* text = "text";
    };

    TEST_CLASS(LinkedListTest) {
    public:

        TEST_METHOD(LinkedList_constructor) {
            {
                TestAllocator a;
                LinkedList<uint32_t, TestAllocator&> list(a);

                Assert::AreEqual(list.Size, 0ull);
                Assert::AreEqual(list.Empty, true);
                Assert::AreEqual(a.Allocations, 0);
            }

            {
                LinkedList<TestClass> list;

                Assert::AreEqual(list.Size, 0ull);
                Assert::AreEqual(list.Empty, true);
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_constructorCopy) {
            LinkedList<uint32_t, TestAllocator> testLinkedList = { 1, 2, 3 };
            LinkedList<uint32_t, TestAllocator> list = LinkedList<uint32_t, TestAllocator>(testLinkedList);

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_constructorMove) {
            LinkedList<uint32_t> testLinkedList = { 1, 2, 3 };
            LinkedList<uint32_t> list = std::move(testLinkedList);

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_constructorInitializer) {
            LinkedList<uint32_t> list = { 1, 2, 3 };

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_referenceAssignment) {
            LinkedList<uint32_t> testLinkedList = { 1, 2, 3 };
            LinkedList<uint32_t> list;
            list = testLinkedList;

            Assert::AreEqual(list.Size, testLinkedList.Size);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_moveAssignment) {
            LinkedList<uint32_t> testLinkedList = { 1, 2, 3 };
            LinkedList<uint32_t> list;
            list = std::move(testLinkedList);

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_initializerAssignment) {
            {
                LinkedList<uint32_t> list;
                list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_add) {
            TestAllocator a;
            {
                LinkedList<uint32_t, TestAllocator&> list(a);
                list.add(1);

                Assert::AreEqual(list.Size, 1ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(a.Allocations, 1);
            }
            Assert::AreEqual(a.Allocations, 0);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_addAll_initializer) {
            TestAllocator a;
            {
                LinkedList<uint32_t, TestAllocator&> list(a);
                list.addAll({ 1, 2, 3 });

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);
                Assert::AreEqual(a.Allocations, 3);
            }
            Assert::AreEqual(a.Allocations, 0);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_addAll_LinkedList) {
            TestAllocator a;
            {
                LinkedList<uint32_t, TestAllocator&> list(a);
                TestAllocator a2;
                const LinkedList<uint32_t, TestAllocator&> testLinkedList = LinkedList<uint32_t, TestAllocator&>({ 1, 2, 3 }, a2);
                list.addAll(testLinkedList);

                Assert::AreEqual(testLinkedList.Size, 3ull);
                Assert::AreEqual(testLinkedList.Empty, false);
                Assert::AreEqual(testLinkedList[0], 1u);
                Assert::AreEqual(testLinkedList[1], 2u);
                Assert::AreEqual(testLinkedList[2], 3u);

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
                Assert::AreEqual(list[2], 3u);

                Assert::AreEqual(list.Size, testLinkedList.Size);
                Assert::AreEqual(a.Allocations, 3);
            }
            Assert::AreEqual(a.Allocations, 0);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_insert) {
            LinkedList<uint32_t> list = { 1, 2, 3 };
            list.insert(1, 4);

            Assert::AreEqual(list.Size, 4ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 4u);
            Assert::AreEqual(list[2], 2u);
            Assert::AreEqual(list[3], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_set) {
            LinkedList<uint32_t> list = { 1, 2, 3 };
            list.set(1, 4);

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 4u);
            Assert::AreEqual(list[2], 3u);
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_get) {
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                auto val = list.get(1);

                Assert::AreEqual(list.Size, 3ull);
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
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_arrayOperator) {
            LinkedList<uint32_t> list = { 1, 2, 3 };
            uint32_t& val = list[1];

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::AreEqual(list[0], 1u);
            Assert::AreEqual(list[1], 2u);
            Assert::AreEqual(list[2], 3u);
            Assert::AreEqual(val, 2u);

            // does it compile with const?
            const LinkedList<uint32_t> list2 = { 1, 2, 3 };
            const uint32_t& val2 = list2[1];

            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_remove) {
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                list.remove(2);

                Assert::AreEqual(list.Size, 2ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 3u);
            }
            {
                LinkedList<uint32_t> list = { 1 };
                list.remove(1);

                Assert::AreEqual(list.Size, 0ull);
                Assert::AreEqual(list.Empty, true);
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_removeAt) {
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };
                list.removeAt(2);

                Assert::AreEqual(list.Size, 2ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list[0], 1u);
                Assert::AreEqual(list[1], 2u);
            }
            {
                LinkedList<uint32_t> list = { 1 };
                list.removeAt(0);

                Assert::AreEqual(list.Size, 0ull);
                Assert::AreEqual(list.Empty, true);
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_removeAll_initializer) {
            LinkedList<uint32_t> list = { 1, 2, 3,4,5,6,7,8 };
            list.removeAll({ 2,4,1 });

            Assert::AreEqual(list.Size, 5ull);
            Assert::AreEqual(list.Empty, false);

            LinkedList<uint32_t> testLinkedList = { 3,5,6,7,8 };
            size_t i = 0;
            //for (auto& item : list)
            //    Assert::AreEqual(item, testLinkedList[i++]);
            _____________________checkMemory();
        }
        TEST_METHOD(LinkedList_iterator) {
            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);

                size_t i = 0;
                //for (auto& item : list)
                //    Assert::AreEqual(item, testVector[i++]);
            }

            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                const LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);

                size_t i = 0;
                for (auto& item : list)
                    Assert::AreEqual(item, testVector[i++]);
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_indexOf) {
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list.indexOf(2), 1ull);
                Assert::AreEqual(list.indexOf(4), 3ull);
            }

            {
                const LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::AreEqual(list.indexOf(2), 1ull);
                Assert::AreEqual(list.indexOf(4), 3ull);
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_contains) {
            {
                LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::IsTrue(list.contains(1));
                Assert::IsFalse(list.contains(4));
            }

            {
                const LinkedList<uint32_t> list = { 1, 2, 3 };

                Assert::AreEqual(list.Size, 3ull);
                Assert::AreEqual(list.Empty, false);
                Assert::IsTrue(list.contains(1));
                Assert::IsFalse(list.contains(4));
            }
            _____________________checkMemory();
        }

        TEST_METHOD(LinkedList_comparison) {
            LinkedList<uint32_t> list = { 1, 2, 3 };
            LinkedList<uint32_t> list2 = { 1, 2, 3 };

            Assert::AreEqual(list.Size, 3ull);
            Assert::AreEqual(list.Empty, false);
            Assert::IsTrue(list == list2);
            _____________________checkMemory();
        }
    };
}
