#include "pch.h"
#include "CppUnitTest.h"
#include "FloatSize.h"

#include "core/resource/ResourceManager.h"
#include "core/window/SystemWindow.h"
#include "core/window/WindowClass.h"
#include "core/Timer.h"
#include "ui/text/textBlock.h"
#include "ui/test/font/FontLoader.h"

#include <format>
#include <ui/RootView.h>
#include <ui/test/text/TextLayout.h>
#include <ui/test/UIContext.h>

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
        Ghurund::Core::Logger::init();
        Ghurund::Core::Logger::log(LogType::INFO, _T("working dir: {}\n"), Ghurund::Core::DirectoryPath(L".").AbsolutePath);
        window = new SystemWindow(WindowClass::WINDOWED, timer);
        context = new UIContext(*window, resourceManager);
        fontLoader = new FontLoader();
        resourceManager.Loaders.set<Font>(std::unique_ptr<FontLoader>(fontLoader));
        Ghurund::Core::SharedPointer<Font> latoMediumFont = resourceManager.load<Font>(Ghurund::Core::FilePath(L"e:/Ghurund/resources/fonts\\lato_medium.ttf"));
        textFormat = new TextFormat(latoMediumFont, 10);
    }

    ~TextBlockTest() {
        delete window;
        delete context;
        delete textFormat;
    }

    TEST_METHOD(textBlock_measureEmptyWrap) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        textBlock->Text = L"";
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 0, 10 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextWrap) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        textBlock->Text = L"test text";
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 90, 10 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 90, 70 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyFill) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        textBlock->Text = L"";
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextFill) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        textBlock->Text = L"test text";
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyPixels) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PIXELS, 50), PreferredSize::Height(PreferredSize::Type::PIXELS, 70) };
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextPixels) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PIXELS, 50), PreferredSize::Height(PreferredSize::Type::PIXELS, 70) };
        textBlock->Text = L"test text";
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyPercent) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PERCENT, 50.0f), PreferredSize::Height(PreferredSize::Type::PERCENT, 70.0f) };
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextPercent) {
        SharedPointer<RootView> rootView = new RootView(*context);
        TextLayout* textLayout = new TextLayout(L"text", Color(0.0f, 0.0f, 0.0f), nullptr);
        SharedPointer<TextBlock> textBlock = new TextBlock(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock;
        textBlock->TextFormat = textFormat;

        textBlock->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PERCENT, 50.0f), PreferredSize::Height(PreferredSize::Type::PERCENT, 70.0f) };
        textBlock->Text = L"test text";
        textBlock->MinSize = { 0, 0 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 50, 70 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        textBlock->MinSize = { 150, 170 };
        textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }
    };
}
