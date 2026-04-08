#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"

#include "core/Colors.h"
#include "core/resource/ResourceManager.h"
#include "core/window/SystemWindow.h"
#include "ui/text/TextLayout.h"
#include "ui/font/FontLoader.h"
#include <ui/font/TextStyleLoader.h>
#include <core/image/ImageLoader.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;

    TEST_CLASS(TextLayoutTest) {
private:
    Timer timer;
    CoroutineThreadPool threadPool = CoroutineThreadPool(4);
    CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
    ResourceManager resourceManager = coroutineScheduler;
    IntrusivePointer<ImageLoader> imageLoader;
    IntrusivePointer<FontLoader> fontLoader;
    IntrusivePointer<TextStyleLoader> textStyleLoader;
    IntrusivePointer<FontAtlasLoader> fontAtlasLoader;
    Ghurund::Core::IntrusivePointer<TextStyle> textStyle;

public:
    TextLayoutTest() {
        imageLoader = makeIntrusive<ImageLoader>();
        resourceManager.Loaders.set<Image>(imageLoader.ref());
        fontLoader = makeIntrusive<FontLoader>();
        resourceManager.Loaders.set<Font>(fontLoader.ref());
        fontAtlasLoader = makeIntrusive<FontAtlasLoader>(resourceManager);
        resourceManager.Loaders.set<FontAtlas>(fontAtlasLoader.ref());
        textStyleLoader = makeIntrusive<TextStyleLoader>(resourceManager);
        resourceManager.Loaders.set<TextStyle>(textStyleLoader.ref());

        FilePath path = Ghurund::Core::FilePath(L"../../resources/textStyles\\lato_medium_12.bin");
        auto coroutine = resourceManager.load<TextStyle>(path, DirectoryPath());
        coroutine.resume();
        textStyle = coroutine.Result;
    }

    ~TextLayoutTest() {
        fontLoader->release();
    }

    TEST_METHOD(textLayout_oneLine) {
        TextLayout* textLayout = ghnew TextLayout(L"one line", textStyle.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 200, 200 };
        textLayout->refresh();
        Assert::AreEqual(1ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(8ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[0].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_twoLines) {
        TextLayout* textLayout = ghnew TextLayout(L"two\nlines", textStyle.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 200, 200 };
        textLayout->refresh();
        Assert::AreEqual(2ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(3ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(1ull, textLayout->Lines[1].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[1].Spans[0].start);
        Assert::AreEqual(5ull, textLayout->Lines[1].Spans[0].finish);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[0].Height);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[1].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_lineBreak_space) {
        TextLayout* textLayout = ghnew TextLayout(L"a b", textStyle.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 10, 200 };
        textLayout->refresh();
        Assert::AreEqual(2ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(1ull, textLayout->Lines[1].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[1].Spans[0].start);
        Assert::AreEqual(1ull, textLayout->Lines[1].Spans[0].finish);
		Assert::AreEqual((uint16_t)(textLayout->Lines[0].Height + textLayout->Lines[1].Ascent), (uint16_t)textLayout->Lines[1].Characters[0].pos.y);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[0].Height);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[1].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_lineBreak_noSpace) {
        TextLayout* textLayout = ghnew TextLayout(L"abc", textStyle.ref(), Colors::BLACK);
        textLayout->breakWords = false;
        textLayout->PreferredSize = { 10, 200 };
        textLayout->refresh();
        Assert::AreEqual(1ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(3ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[0].Height);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_wordBreak_noSpace) {
        TextLayout* textLayout = ghnew TextLayout(L"abc", textStyle.ref(), Colors::BLACK);
        textLayout->breakWords = true;
        textLayout->PreferredSize = { 10, 200 };
        textLayout->refresh();
        Assert::AreEqual(3ull, textLayout->Lines.Size);
        for (size_t i = 0; i < 3; i++) {
            Assert::AreEqual(1ull, textLayout->Lines[i].Spans.Size);
            Assert::AreEqual(0ull, textLayout->Lines[i].Spans[0].start);
            Assert::AreEqual(1ull, textLayout->Lines[i].Spans[0].finish);
            Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[i].Height);
        }
        Assert::AreEqual((uint16_t)(textLayout->Lines[0].Height + textLayout->Lines[1].Ascent), (uint16_t)textLayout->Lines[1].Characters[0].pos.y);
		Assert::AreEqual((uint16_t)(textLayout->Lines[0].Height + textLayout->Lines[1].Height + textLayout->Lines[2].Ascent), (uint16_t)textLayout->Lines[2].Characters[0].pos.y);
        Assert::IsTrue(textLayout->validate());
    }

    TEST_METHOD(textLayout_missingGlyph) {
        TextLayout* textLayout = ghnew TextLayout(L"mìssing", textStyle.ref(), Colors::BLACK);
        textLayout->PreferredSize = { 200, 200 };
        textLayout->refresh();
        Assert::AreEqual(1ull, textLayout->Lines.Size);
        Assert::AreEqual(1ull, textLayout->Lines[0].Spans.Size);
        Assert::AreEqual(0ull, textLayout->Lines[0].Spans[0].start);
        Assert::AreEqual(6ull, textLayout->Lines[0].Spans[0].finish);
        Assert::AreEqual(textStyle->FontMetrics.height, textLayout->Lines[0].Height);
    }
    };
}
