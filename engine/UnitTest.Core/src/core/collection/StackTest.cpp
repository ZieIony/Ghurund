#include "pch.h"
#include "CppUnitTest.h"

#include "core/collection/List.h"
#include "core/collection/Stack.h"

#include <iostream>
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Core;
    using namespace std;

    TEST_CLASS(StackTest) {
public:

    TEST_METHOD(Stack_constructor) {
        Stack<uint32_t> stack;

        Assert::AreEqual(stack.Size, (size_t)0);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, true);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_constructorInitial) {
        Stack<uint32_t> stack(20);

        Assert::AreEqual(stack.Size, (size_t)0);
        Assert::AreEqual(stack.Capacity, (size_t)20);
        Assert::AreEqual(stack.Empty, true);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_constructorCopy) {
        Stack<uint32_t> testStack = { 1, 2, 3 };
        Stack<uint32_t> stack = Stack<uint32_t>(testStack);

        Assert::AreEqual(stack.Size, testStack.Size);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testStack.begin();
        auto j = stack.begin();
        for (; i != testStack.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_constructorMove) {
        std::initializer_list<uint32_t> testList = { 1, 2, 3 };
        Stack<uint32_t> testStack = testList;
        Stack<uint32_t> stack = std::move(testStack);

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testList.begin();
        auto j = stack.begin();
        for (; i != testList.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_constructorInitializer) {
        std::initializer_list<uint32_t> testList = { 1, 2, 3 };
        Stack<uint32_t> stack = testList;

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testList.begin();
        auto j = stack.begin();
        for (; i != testList.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_listReferenceAssignment) {
        List<uint32_t> testList = { 1, 2, 3 };
        Stack<uint32_t> stack;
        stack = testList;

        Assert::AreEqual(stack.Size, testList.Size);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testList.begin();
        auto j = stack.begin();
        for (; i != testList.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_referenceAssignment) {
        Stack<uint32_t> testStack = { 1, 2, 3 };
        Stack<uint32_t> stack;
        stack = testStack;

        Assert::AreEqual(stack.Size, testStack.Size);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testStack.begin();
        auto j = stack.begin();
        for (; i != testStack.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_moveAssignment) {
        std::initializer_list<uint32_t> testList = { 1, 2, 3 };
        Stack<uint32_t> testStack = testList;
        Stack<uint32_t> stack;
        stack = std::move(testStack);

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testList.begin();
        auto j = stack.begin();
        for (; i != testList.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_initializerAssignment) {
        std::initializer_list<uint32_t> testList = { 1, 2, 3 };
        Stack<uint32_t> stack;
        stack = testList;

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testList.begin();
        auto j = stack.begin();
        for (; i != testList.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_push) {
        Stack<uint32_t> stack;
        stack.push(1);

        Assert::AreEqual(stack.Size, (size_t)1);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        Assert::AreEqual(stack.top(), 1u);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_pushAll_initializer) {
        std::initializer_list<uint32_t> testList = { 1, 2, 3 };
        Stack<uint32_t> stack;
        stack.pushAll(testList);

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        auto i = testList.begin();
        auto j = stack.begin();
        for (; i != testList.end(); i++, j++)
            Assert::AreEqual(*i, *j);
        _____________________checkMemory();
    }
    /*
    TEST_METHOD(Stack_pushAll_Stack) {
        Stack<uint32_t> stack;
        const Stack<uint32_t> testStack = { 1, 2, 3 };
        stack.pushAll(testStack);

        Assert::AreEqual(testStack.Size, (size_t)3);
        Assert::AreEqual(testStack.Capacity >= stack.Size, true);
        Assert::AreEqual(testStack.Empty, false);
        Assert::AreEqual(stack, { 1, 2, 3 });

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        Assert::AreEqual(stack, { 1, 2, 3 });

        Assert::AreEqual(stack.Size, testStack.Size);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_remove) {
        Stack<uint32_t> stack = { 1, 2, 3 };
        uint32_t val = stack.pop();

        Assert::AreEqual(stack.Size, (size_t)2);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        Assert::AreEqual(stack, { 1, 2 });
        Assert::AreEqual(val, 3u);
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_iterator) {
        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            Stack<uint32_t> stack = { 1, 2, 3 };

            Assert::AreEqual(stack.Size, (size_t)3);
            Assert::AreEqual(stack.Capacity >= stack.Size, true);
            Assert::AreEqual(stack.Empty, false);

            size_t i = 0;
            for (auto& item : stack)
                Assert::AreEqual(item, testVector[i++]);
        }

        {
            std::vector<uint32_t> testVector = { 1, 2, 3 };
            const Stack<uint32_t> stack = { 1, 2, 3 };

            Assert::AreEqual(stack.Size, (size_t)3);
            Assert::AreEqual(stack.Capacity >= stack.Size, true);
            Assert::AreEqual(stack.Empty, false);

            size_t i = 0;
            for (auto& item : stack)
                Assert::AreEqual(item, testVector[i++]);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_indexOf) {
        {
            Stack<uint32_t> stack = { 1, 2, 3 };

            Assert::AreEqual(stack.Size, (size_t)3);
            Assert::AreEqual(stack.Capacity >= stack.Size, true);
            Assert::AreEqual(stack.Empty, false);
            Assert::AreEqual(stack.indexOf(2), (size_t)1);
            Assert::AreEqual(stack.indexOf(4), (size_t)3);
        }

        {
            const Stack<uint32_t> stack = { 1, 2, 3 };

            Assert::AreEqual(stack.Size, (size_t)3);
            Assert::AreEqual(stack.Capacity >= stack.Size, true);
            Assert::AreEqual(stack.Empty, false);
            Assert::AreEqual(stack.indexOf(2), (size_t)1);
            Assert::AreEqual(stack.indexOf(4), (size_t)3);
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_contains) {
        {
            Stack<uint32_t> stack = { 1, 2, 3 };

            Assert::AreEqual(stack.Size, (size_t)3);
            Assert::AreEqual(stack.Capacity >= stack.Size, true);
            Assert::AreEqual(stack.Empty, false);
            Assert::IsTrue(stack.contains(1));
            Assert::IsFalse(stack.contains(4));
        }

        {
            const Stack<uint32_t> stack = { 1, 2, 3 };

            Assert::AreEqual(stack.Size, (size_t)3);
            Assert::AreEqual(stack.Capacity >= stack.Size, true);
            Assert::AreEqual(stack.Empty, false);
            Assert::IsTrue(stack.contains(1));
            Assert::IsFalse(stack.contains(4));
        }
        _____________________checkMemory();
    }

    TEST_METHOD(Stack_comparison) {
        Stack<uint32_t> stack = { 1, 2, 3 };
        Stack<uint32_t> stack2 = { 1, 2, 3 };

        Assert::AreEqual(stack.Size, (size_t)3);
        Assert::AreEqual(stack.Capacity >= stack.Size, true);
        Assert::AreEqual(stack.Empty, false);
        Assert::IsTrue(stack == stack2);
        _____________________checkMemory();
    }*/
    };
}
