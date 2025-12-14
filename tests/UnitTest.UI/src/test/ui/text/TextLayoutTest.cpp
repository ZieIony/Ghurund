#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"

#include "core/Colors.h"
#include "core/resource/ResourceManager.h"
#include "core/window/SystemWindow.h"
#include "ui/text/TextLayout.h"
#include "ui/font/FontLoader.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;

    TEST_CLASS(TextLayoutTest) {
private:
    ResourceManager resourceManager;
    FontLoader* fontLoader;
    Ghurund::Core::IntrusivePointer<Font> latoMediumFont;

public:
    TextLayoutTest() {
        fontLoader = ghnew FontLoader();
        resourceManager.Loaders.set<Font>(*fontLoader);
        ResourcePath path = Ghurund::Core::FilePath(L"../../resources/fonts\\lato_medium.ttf");
        latoMediumFont = Ghurund::Core::IntrusivePointer<Font>(resourceManager.load<Font>(path, DirectoryPath()));
    }

    ~TextLayoutTest() {
        fontLoader->release();
    }

    TEST_METHOD(textLayout_oneLine) {
        TextLayout* textLayout = ghnew TextLayout(L"one line", latoMediumFont.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 200, 200 };
        textLayout->refresh();
        Assert::AreEqual(1ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(8ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[0].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_twoLines) {
        TextLayout* textLayout = ghnew TextLayout(L"two\nlines", latoMediumFont.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 200, 200 };
        textLayout->refresh();
        Assert::AreEqual(2ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(3ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(1ull, textLayout->Lines[1].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[1].Spans[0].start);
        Assert::AreEqual(5ull, textLayout->Lines[1].Spans[0].finish);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[0].Height);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[1].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_lineBreak_space) {
        TextLayout* textLayout = ghnew TextLayout(L"a b", latoMediumFont.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 10, 200 };
        textLayout->refresh();
        Assert::AreEqual(2ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(1ull, textLayout->Lines[1].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[1].Spans[0].start);
        Assert::AreEqual(1ull, textLayout->Lines[1].Spans[0].finish);
        Assert::AreEqual(textLayout->Lines[0].Height, (uint32_t)textLayout->Lines[1].Characters[0].pos.y);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[0].Height);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[1].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_lineBreak_noSpace) {
        TextLayout* textLayout = ghnew TextLayout(L"abc", latoMediumFont.ref(), Colors::BLACK);
        textLayout->breakWords = false;
        textLayout->PreferredSize = { 10, 200 };
        textLayout->refresh();
        Assert::AreEqual(1ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(3ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[0].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_wordBreak_noSpace) {
        TextLayout* textLayout = ghnew TextLayout(L"abc", latoMediumFont.ref(), Colors::BLACK);
        textLayout->breakWords = true;
        textLayout->PreferredSize = { 10, 200 };
        textLayout->refresh();
        Assert::AreEqual(3ull, textLayout->Lines.Size);
        for (size_t i = 0; i < 3; i++) {
            Assert::AreEqual(1ull, textLayout->Lines[i].Spans.Size);
            Assert::AreEqual(0ull, textLayout->Lines[i].Spans[0].start);
            Assert::AreEqual(1ull, textLayout->Lines[i].Spans[0].finish);
            Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[i].Height);
        }
        Assert::AreEqual(textLayout->Lines[0].Height, (uint32_t)textLayout->Lines[1].Characters[0].pos.y);
		Assert::AreEqual(textLayout->Lines[0].Height + textLayout->Lines[1].Height, (uint32_t)textLayout->Lines[2].Characters[0].pos.y);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_missingGlyph) {
        TextLayout* textLayout = ghnew TextLayout(L"mìssing", latoMediumFont.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 200, 200 };
        textLayout->refresh();
        Assert::AreEqual(1ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(6ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(latoMediumFont->Height, textLayout->Lines[0].Height);
    }
    };
}
