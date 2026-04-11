#include "utcpch.h"
#include "CppUnitTest.h"
#include "test/utils/MemoryGuard.h"

#include "core/application/Settings.h"
#include "core/DataParsing.h"
#include "core/math/Int.h"
#include "core/string/TextConversionUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace UnitTest::Utils;
    using namespace Ghurund::Core;

    TEST_CLASS(SettingsTest) {
private:
    AString settingsText = R"(
<Settings>
    <Property name="width" value="800"/>
    <Property name="height" value="600"/>
</Settings>
)";
public:

    TEST_METHOD(Settings_read) {
        MemoryGuard guard;
        {
            Settings settings;
            settings.load(settingsText.Data, settingsText.Size);
            uint32_t width = parse<uint32_t>(convertText<wchar_t, char>(settings.get(L"width")));
            Assert::AreEqual(800u, width);
            uint32_t height = parse<uint32_t>(convertText<wchar_t, char>(settings.get(L"height")));
            Assert::AreEqual(600u, height);
        }
    }
    };
}