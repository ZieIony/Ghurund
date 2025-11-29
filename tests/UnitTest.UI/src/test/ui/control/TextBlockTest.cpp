#include "utuipch.h"
#include "CppUnitTest.h"
#include "test/utils/TestUtils.h"

#include "core/resource/ResourceManager.h"
#include "core/window/SystemWindow.h"
#include "core/window/WindowClass.h"
#include "core/Timer.h"
#include "ui/text/TextBlock.h"
#include "ui/font/FontLoader.h"
#include "ui/RootView.h"
#include "test/ui/text/TextLayout.h"
#include "test/ui/TestUIContext.h"

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
        context = ghnew TestUIContext(*window);
        fontLoader = ghnew FontLoader();
        resourceManager.Loaders.set<Font>(*fontLoader);
        ResourcePath path = Ghurund::Core::FilePath(L"../../resources/fonts\\lato_medium.ttf");
        Ghurund::Core::IntrusivePointer<Font> latoMediumFont(resourceManager.load<Font>(path, DirectoryPath()));
        textFormat = ghnew TextFormat(latoMediumFont.get(), 10);
    }

    ~TextBlockTest() {
        fontLoader->release();
        delete window;
        delete context;
        delete textFormat;
    }
    /*
    TEST_METHOD(textBlock_measureEmptyWrap) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width::WRAP, ContentSize::Height::WRAP };
        textBlock->Text = L"";
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 0, 10 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextWrap) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width::WRAP, ContentSize::Height::WRAP };
        textBlock->Text = L"test typeName";
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 90, 10 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 90, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyFill) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
        textBlock->Text = L"";
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextFill) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
        textBlock->Text = L"test typeName";
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyPixels) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width(ContentSize::Type::PIXELS, 50), ContentSize::Height(ContentSize::Type::PIXELS, 70) };
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextPixels) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width(ContentSize::Type::PIXELS, 50), ContentSize::Height(ContentSize::Type::PIXELS, 70) };
        textBlock->Text = L"test typeName";
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureEmptyPercent) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width(ContentSize::Type::PERCENT, 50.0f), ContentSize::Height(ContentSize::Type::PERCENT, 70.0f) };
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }

    TEST_METHOD(textBlock_measureTextPercent) {
        auto rootView = makeIntrusive<RootView>(*context);
        TextLayout* textLayout = ghnew TextLayout(L"typeName", Color(0.0f, 0.0f, 0.0f), textFormat);
        auto textBlock = makeIntrusive<TextBlock>(std::unique_ptr<TextLayout>(textLayout));
        rootView->Child = textBlock.get();

        //textBlock->ContentSize = { ContentSize::Width(ContentSize::Type::PERCENT, 50.0f), ContentSize::Height(ContentSize::Type::PERCENT, 70.0f) };
        textBlock->Text = L"test typeName";
        //textBlock->MinSize = { 0, 0 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 50, 70 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, textBlock->MeasuredSize);
        //textBlock->MinSize = { 150, 170 };
        //textBlock->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, textBlock->MeasuredSize);
    }*/
    };
}
