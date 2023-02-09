#include "pch.h"
#include "CppUnitTest.h"
#include "test/TestUtils.h"

#include "core/resource/ResourceManager.h"
#include "core/window/SystemWindow.h"
#include "core/window/WindowClass.h"
#include "core/Timer.h"
#include "ui/text/TextBlock.h"
#include "ui/font/FontLoader.h"
#include "ui/RootView.h"
#include "test/ui/text/TextLayout.h"
#include "test/ui/UIContext.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;

    TEST_CLASS(TextBlockTest) {
private:
    ResourceManager resourceManager;
    Timer timer;
    Window* window;
    UIContext* context;
    TextFormat* textFormat;
    FontLoader* fontLoader;

public:
    TextBlockTest() {
        window = ghnew SystemWindow(timer);
        context = ghnew UIContext(*window, resourceManager);
        fontLoader = ghnew FontLoader();
        resourceManager.Loaders.set<Font>(std::unique_ptr<FontLoader>(fontLoader));
        Ghurund::Core::SharedPointer<Font> latoMediumFont(resourceManager.load<Font>(Ghurund::Core::FilePath(L"e:/Ghurund/resources/fonts\\lato_medium.ttf")));
        textFormat = ghnew TextFormat(latoMediumFont.get(), 10);
    }

    ~TextBlockTest() {
        delete window;
        delete context;
        delete textFormat;
    }

    TEST_METHOD(textBlock_measureEmptyWrap) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        textBlock->Text = L"";
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 0, 10 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextWrap) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        textBlock->Text = L"test text";
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 90, 10 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 90, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyFill) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        textBlock->Text = L"";
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextFill) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        textBlock->Text = L"test text";
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyPixels) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PIXELS, 50), PreferredSize::Height(PreferredSize::Type::PIXELS, 70) };
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextPixels) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PIXELS, 50), PreferredSize::Height(PreferredSize::Type::PIXELS, 70) };
        textBlock->Text = L"test text";
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyPercent) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PERCENT, 50.0f), PreferredSize::Height(PreferredSize::Type::PERCENT, 70.0f) };
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextPercent) {
        auto rootView = makeShared<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeShared<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PERCENT, 50.0f), PreferredSize::Height(PreferredSize::Type::PERCENT, 70.0f) };
        textBlock->Text = L"test text";
        //textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }
    };
}
