#include "pch.h"
#include "CppUnitTest.h"
#include "test/ui/image/TestImage.h"
#include "test/TestUtils.h"
#include "test/ui/control/ControlTestTemplate.h"

#include "test/ui/image/Bitmap.h"
#include "ui/control/ImageView.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(ImageViewTest) {
public:

    TEST_METHOD(measureEmptyWrap) {
        UnitTest::Utils::measureEmptyWrap<ImageView>();
    }

    TEST_METHOD(measureImageWrap) {
        UnitTest::Utils::measureContentWrap<ImageView>([](ImageView& imageView) {
            SharedPointer<TestImage> testImage = new TestImage();
            testImage->setPreferredSize({ 20, 30 });
            imageView.Image = testImage;
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyFill) {
        UnitTest::Utils::measureEmptyFill<ImageView>();
    }

    TEST_METHOD(measureImageFill) {
        UnitTest::Utils::measureContentFill<ImageView>([](ImageView& imageView) {
            SharedPointer<TestImage> testImage = new TestImage();
            testImage->setPreferredSize({ 20, 30 });
            imageView.Image = testImage;
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyPixels) {
        UnitTest::Utils::measureEmptyPixels<ImageView>();
    }

    TEST_METHOD(measureImagePixels) {
        UnitTest::Utils::measureContentPixels<ImageView>([](ImageView& imageView) {
            SharedPointer<TestImage> testImage = new TestImage();
            testImage->setPreferredSize({ 20, 30 });
            imageView.Image = testImage;
            return FloatSize{ 20, 30 };
        });
    }

    TEST_METHOD(measureEmptyPercent) {
        UnitTest::Utils::measureEmptyPercent<ImageView>();
    }

    TEST_METHOD(measureImagePercent) {
        UnitTest::Utils::measureContentPercent<ImageView>([](ImageView& imageView) {
            SharedPointer<TestImage> testImage = new TestImage();
            testImage->setPreferredSize({ 20, 30 });
            imageView.Image = testImage;
            return FloatSize{ 20, 30 };
        });
    }
    };
}
