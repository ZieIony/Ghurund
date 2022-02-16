#include "pch.h"
#include "CppUnitTest.h"

#include "core/reflection/BaseType.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    TEST_CLASS(BaseTypeTest) {
public:

    TEST_METHOD(BaseType_same) {
        typedef Ghurund::Core::BaseType<int>::type A;
        typedef Ghurund::Core::BaseType<int*>::type B;
        typedef Ghurund::Core::BaseType<int* const*>::type C;
        typedef Ghurund::Core::BaseType<const int*>::type D;
        typedef Ghurund::Core::BaseType<int* const>::type E;
        typedef Ghurund::Core::BaseType<int* const&>::type F;
        typedef Ghurund::Core::BaseType<const int>::type G;
        typedef Ghurund::Core::BaseType<const volatile int>::type H;
        typedef Ghurund::Core::BaseType<volatile int&>::type I;

        Assert::IsTrue(std::is_same<int, A>::value);
        Assert::IsTrue(std::is_same<int, B>::value);
        Assert::IsTrue(std::is_same<int, C>::value);
        Assert::IsTrue(std::is_same<int, D>::value);
        Assert::IsTrue(std::is_same<int, E>::value);
        Assert::IsTrue(std::is_same<int, F>::value);
        Assert::IsTrue(std::is_same<int, G>::value);
        Assert::IsTrue(std::is_same<int, H>::value);
        Assert::IsTrue(std::is_same<int, I>::value);
    }
    };
}
