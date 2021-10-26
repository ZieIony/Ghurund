#include "pch.h"
#include "CppUnitTest.h"
#include "TestImage.h"
#include "FloatSize.h"

#include "ui/test/image/Bitmap.h"
#include "ui/control/ImageView.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ImageViewTest) {
public:

    TEST_METHOD(ImageView_measureEmptyWrap) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 0, 0 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureImageWrap) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
        SharedPointer<TestImage> testImage = new TestImage();
        testImage->setPreferredSize({ 20, 30 });
        imageView->Image = testImage;
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 20, 30 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureEmptyFill) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureImageFill) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        SharedPointer<TestImage> testImage = new TestImage();
        testImage->setPreferredSize({ 20, 30 });
        imageView->Image = testImage;
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 100, 120 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureEmptyPixels) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PIXELS, 50), PreferredSize::Height(PreferredSize::Type::PIXELS, 70) };
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureImagePixels) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PIXELS, 50), PreferredSize::Height(PreferredSize::Type::PIXELS, 70) };
        SharedPointer<TestImage> testImage = new TestImage();
        testImage->setPreferredSize({ 20, 30 });
        imageView->Image = testImage;
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 70 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureEmptyPercent) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PERCENT, 50.0f), PreferredSize::Height(PreferredSize::Type::PERCENT, 70.0f) };
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }

    TEST_METHOD(ImageView_measureImagePercent) {
        SharedPointer<ImageView> imageView = new ImageView();
        imageView->PreferredSize = { PreferredSize::Width(PreferredSize::Type::PERCENT, 50.0f), PreferredSize::Height(PreferredSize::Type::PERCENT, 70.0f) };
        SharedPointer<TestImage> testImage = new TestImage();
        testImage->setPreferredSize({ 20, 30 });
        imageView->Image = testImage;
        imageView->MinSize = { 0, 0 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, imageView->MeasuredSize);
        imageView->MinSize = { 50, 70 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 50, 84 }, imageView->MeasuredSize);
        imageView->MinSize = { 150, 170 };
        imageView->measure(100, 120);
        Assert::AreEqual(FloatSize{ 150, 170 }, imageView->MeasuredSize);
    }
    };
}
