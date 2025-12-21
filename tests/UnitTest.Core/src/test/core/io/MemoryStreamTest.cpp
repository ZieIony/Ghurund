#include "utcpch.h"
#include "CppUnitTest.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestUtils.h"

#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(MemoryStreamTest) {
private:
    struct TestStruct {
        int i;
        float f;
        bool b;

        inline bool operator==(const TestStruct& other) const = default;
    };

public:

    TEST_METHOD(MemoryStream_int32) {
        MemoryGuard guard;
        {
            int32_t i = -7;
            MemoryOutputStream os;
            os.writeInt32(i);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(i, is.readInt32());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_uint32) {
        MemoryGuard guard;
        {
            uint32_t i = 17;
            MemoryOutputStream os;
            os.writeUInt32(i);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(i, is.readUInt32());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_int64) {
        MemoryGuard guard;
        {
            int64_t i = -8;
            MemoryOutputStream os;
            os.writeInt64(i);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(i, is.readInt64());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_uint64) {
        MemoryGuard guard;
        {
            uint64_t i = 56;
            MemoryOutputStream os;
            os.writeUInt64(i);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(i, is.readUInt64());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_float) {
        MemoryGuard guard;
        {
            float f = 2.57f;
            MemoryOutputStream os;
            os.writeFloat(f);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(f, is.readFloat());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_double) {
        MemoryGuard guard;
        {
            double d = 3.14;
            MemoryOutputStream os;
            os.writeDouble(d);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(d, is.readDouble());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_boolean) {
        MemoryGuard guard;
        {
            bool b = true, b2 = false;
            MemoryOutputStream os;
            os.writeBoolean(b);
            os.writeBoolean(b2);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(b, is.readBoolean());
            Assert::AreEqual(b2, is.readBoolean());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_ASCII) {
        MemoryGuard guard;
        {
            const char* str = "asdf";
            AString str2 = "test";
            const char* str3 = "view";
            AStringView sv = str3;
            MemoryOutputStream os;
            os.writeASCII(str);
            os.writeASCII(str2);
            os.writeASCII(sv);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(AString(str), is.readASCII());
            Assert::AreEqual(str2, is.readASCII());
            Assert::AreEqual(AString(str3), is.readASCII());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_Unicode) {
        MemoryGuard guard;
        {
            const wchar_t* str = L"asdf";
            WString str2 = L"test";
            const wchar_t* str3 = L"view";
            WStringView sv = str3;
            MemoryOutputStream os;
            os.writeUnicode(str);
            os.writeUnicode(str2);
            os.writeUnicode(sv);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            Assert::AreEqual(WString(str), is.readUnicode());
            Assert::AreEqual(str2, is.readUnicode());
            Assert::AreEqual(WString(str3), is.readUnicode());
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_bytes) {
        MemoryGuard guard;
        {
            TestStruct t = { 4, 5.21f, true };
            MemoryOutputStream os;
            os.writeBytes(&t, sizeof(t));
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            TestStruct t2 = *(TestStruct*)is.readBytes(sizeof(TestStruct));
            Assert::IsTrue(t == t2);
            Assert::AreEqual(0ull, is.Available);
        }
    }

    TEST_METHOD(MemoryStream_template) {
        MemoryGuard guard;
        {
            TestStruct t = { 4, 5.21f, true };
            MemoryOutputStream os;
            os.write(t);
            MemoryInputStream is(os.Data, os.BytesWritten);
            Assert::AreEqual(os.BytesWritten, is.Available);
            TestStruct t2 = is.read<TestStruct>();
            Assert::IsTrue(t == t2);
            Assert::AreEqual(0ull, is.Available);
        }
    }
    };
}
