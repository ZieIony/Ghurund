#include "pch.h"
#include "CppUnitTest.h"
#include "test/MemoryGuard.h"
#include "test/core/collection/TestAllocator.h"

#include "core/collection/Set.h"
#include "core/collection/Stack.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;
    using namespace std;

    TEST_CLASS(SetTest) {
    public:

        TEST_METHOD(Set_constructor) {
            MemoryGuard guard;
            {
                Set<uint32_t> set;

                Assert::AreEqual(set.Size, (size_t)0);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, true);
            }

            {
                Set<TestClass> set;

                Assert::AreEqual(set.Size, (size_t)0);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, true);
            }
        }

        TEST_METHOD(Set_constructorInitial) {
            MemoryGuard guard;
            {
                Set<uint32_t> set(20);

                Assert::AreEqual(set.Size, (size_t)0);
                Assert::AreEqual(set.Capacity, (size_t)20);
                Assert::AreEqual(set.Empty, true);
            }

            {
                Set<TestClass> set(20);

                Assert::AreEqual(set.Size, (size_t)0);
                Assert::AreEqual(set.Capacity, (size_t)20);
                Assert::AreEqual(set.Empty, true);
            }
        }

        TEST_METHOD(Set_constructorCopy) {
            Set<uint32_t> testSet = { 1u, 2u, 3u };
            {
                MemoryGuard guard;
                {
                    Set<uint32_t> set = Set<uint32_t>(testSet);

                    Assert::AreEqual(set.Size, (size_t)3);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);
                    for (auto val : { 1, 2, 3 })
                        Assert::IsTrue(set.contains(val));
                }
            }
        }

        TEST_METHOD(Set_constructorMove) {
            MemoryGuard guard;
            {
                Set<uint32_t> testSet = { 1u, 2u, 3u };
                Set<uint32_t> set = std::move(testSet);

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1, 2, 3 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(Set_constructor_initializer) {
            MemoryGuard guard;
            {
                Set<uint32_t> set = { 1u, 2u, 3u };

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1, 2, 3 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(Set_constructor_initializerWithDuplicates) {
            MemoryGuard guard;
            {
                Set<uint32_t> set = { 1u, 2u, 3u, 2u, 1u };

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1, 2, 3 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(Set_referenceAssignment) {
            Stack<uint32_t> testStack = { 1u, 2u, 3u };
            Set<uint32_t> set;
            {
                MemoryGuard guard;
                {
                    set = testStack;

                    Assert::AreEqual(set.Size, testStack.Size);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);
                    for (auto val : { 1, 2, 3 })
                        Assert::IsTrue(set.contains(val));
                }
            }
        }

        TEST_METHOD(Set_moveAssignment) {
            MemoryGuard guard;
            {
                Set<uint32_t> testSet = { 1u, 2u, 3u };
                Set<uint32_t> set;
                set = std::move(testSet);

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1, 2, 3 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(Set_moveAssignment_differentAllocators) {
            TestAllocator allocator1;
            Set<uint32_t, TestAllocator> testSet = allocator1;
            TestAllocator allocator2;
            Set<uint32_t, TestAllocator> set = allocator2;
            {
                MemoryGuard guard;
                {
                    auto func = [&] { set = std::move(testSet); };
                    Assert::ExpectException<IncompatibleAllocatorsException>(func);
                }
            }
        }

        TEST_METHOD(Set_initializerAssignment) {
            Set<uint32_t> set;
            {
                MemoryGuard guard;
                {
                    set = { 1, 2, 3 };

                    Assert::AreEqual(set.Size, (size_t)3);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);
                    for (auto val : { 1, 2, 3 })
                        Assert::IsTrue(set.contains(val));
                }
            }
        }

        TEST_METHOD(TestSetAdd) {
            MemoryGuard guard;
            {
                Set<uint32_t> set;
                set.add(1);

                Assert::AreEqual(set.Size, (size_t)1);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(TestSetAddAllInitializer) {
            MemoryGuard guard;
            {
                Set<uint32_t> set;
                set.addAll({ 1, 2, 3 });

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1, 2, 3 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(Set_addAll_Set) {
            Set<uint32_t> set;
            const Set<uint32_t> testSet = { 1, 2, 3 };
            {
                MemoryGuard guard;
                {
                    set.addAll(testSet);

                    Assert::AreEqual(testSet.Size, (size_t)3);
                    Assert::AreEqual(testSet.Capacity >= set.Size, true);
                    Assert::AreEqual(testSet.Empty, false);
                    for (auto val : { 1, 2, 3 })
                        Assert::IsTrue(set.contains(val));

                    Assert::AreEqual(set.Size, (size_t)3);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);
                    for (auto val : { 1, 2, 3 })
                        Assert::IsTrue(set.contains(val));

                    Assert::AreEqual(set.Size, testSet.Size);
                }
            }
        }

        TEST_METHOD(Set_addAll_ListDuplicates) {
            MemoryGuard guard;
            {
                Set<uint32_t> set;
                const List<uint32_t> testList = { 1, 2, 3, 2, 1 };
                set.addAll(testList);

                Assert::AreEqual(testList.Size, (size_t)5);
                Assert::AreEqual(testList.Capacity >= set.Size, true);
                Assert::AreEqual(testList.Empty, false);
                for (auto val : { 1, 2, 3, 2, 1 })
                    Assert::IsTrue(testList.contains(val));

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                for (auto val : { 1, 2, 3 })
                    Assert::IsTrue(set.contains(val));
            }
        }

        TEST_METHOD(Set_remove) {
            Set<uint32_t> set = { 1, 2, 3 };
            {
                MemoryGuard guard;
                {
                    set.remove(2);

                    Assert::AreEqual(set.Size, (size_t)2);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);
                    for (auto val : { 1, 3 })
                        Assert::IsTrue(set.contains(val));
                }
            }
        }

        TEST_METHOD(Set_iterator) {
            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                Set<uint32_t> set = { 1, 2, 3 };
                {
                    MemoryGuard guard;

                    Assert::AreEqual(set.Size, (size_t)3);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);

                    size_t i = 0;
                    for (auto& item : set)
                        Assert::AreEqual(item, testVector[i++]);
                }
            }
        }

        TEST_METHOD(Set_constIterator) {
            {
                std::vector<uint32_t> testVector = { 1, 2, 3 };
                const Set<uint32_t> set = { 1, 2, 3 };
                {
                    MemoryGuard guard;

                    Assert::AreEqual(set.Size, (size_t)3);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);

                    size_t i = 0;
                    for (auto& item : set)
                        Assert::AreEqual(item, testVector[i++]);
                }
            }
        }

        TEST_METHOD(Set_contains) {
            Set<uint32_t> set = { 1, 2, 3 };
            {
                MemoryGuard guard;

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                Assert::IsTrue(set.contains(1));
                Assert::IsFalse(set.contains(4));
            }
        }

        TEST_METHOD(Set_contains_const) {
            const Set<uint32_t> set = { 1, 2, 3 };
            {
                MemoryGuard guard;

                Assert::AreEqual(set.Size, (size_t)3);
                Assert::AreEqual(set.Capacity >= set.Size, true);
                Assert::AreEqual(set.Empty, false);
                Assert::IsTrue(set.contains(1));
                Assert::IsFalse(set.contains(4));
            }
        }

        TEST_METHOD(Set_comparison) {
            Set<uint32_t> set = { 1, 2, 3 };
            Set<uint32_t> set2 = { 1, 2, 3 };
            {
                MemoryGuard guard;
                {
                    Assert::AreEqual(set.Size, (size_t)3);
                    Assert::AreEqual(set.Capacity >= set.Size, true);
                    Assert::AreEqual(set.Empty, false);
                    Assert::IsTrue(set == set2);
                }
            }
        }
    };
}
