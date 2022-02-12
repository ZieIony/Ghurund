#include "pch.h"
#include "CppUnitTest.h"

#include "TestClass.h"
#include "MemoryGuard.h"
#include "core/reflection/StandardTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<> static std::wstring ToString<Ghurund::Core::Type>(const Ghurund::Core::Type& t) {
        return convertText<char, wchar_t>(t.Name).Data;
    }

    template<> static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
        return convertText<char, wchar_t>(t).Data;
    }
}

namespace UnitTest {
    TEST_CLASS(TypeTest) {
public:

    TEST_METHOD(Type_uint32) {
        const Ghurund::Core::Type& intType = Ghurund::Core::getType<uint32_t>();
        Assert::AreEqual(AString("uint32_t"), intType.Name);
        Assert::AreEqual(sizeof(uint32_t), intType.Size);
        Assert::IsFalse(intType.IsConst);
        Assert::IsFalse(intType.IsPointer);
        Assert::IsFalse(intType.IsReference);
        Assert::IsFalse(intType.IsVolatile);
        Assert::IsFalse(intType.IsTemplate);
        Assert::AreEqual(intType, intType.BaseType);
    }

    TEST_METHOD(Type_pointer) {
        // MemoryGuard reports a leak here, because Ghurund::Core::getType<uint32_t*>() makes a new static object
        const Ghurund::Core::Type& intPtrType = Ghurund::Core::getType<uint32_t*>();
        Assert::AreEqual(AString("uint32_t"), intPtrType.Name);
        Assert::AreEqual(sizeof(uint32_t), intPtrType.Size);
        Assert::IsFalse(intPtrType.IsConst);
        Assert::IsTrue(intPtrType.IsPointer);
        Assert::IsFalse(intPtrType.IsReference);
        Assert::IsFalse(intPtrType.IsVolatile);
        Assert::IsFalse(intPtrType.IsTemplate);
        Assert::AreNotEqual(intPtrType, intPtrType.BaseType);

        const Ghurund::Core::Type& intType = Ghurund::Core::getType<uint32_t>();
        Assert::AreNotEqual(intPtrType, intType.BaseType);
    }
    };
}
