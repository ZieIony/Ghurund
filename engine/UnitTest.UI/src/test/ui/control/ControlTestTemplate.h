#pragma once

#include "core/math/Size.h"
#include "test/MemoryGuard.h"
#include "core/SharedPointer.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace UnitTest::Utils {
    using namespace Ghurund::Core;

    template<class T>
    void measureEmptyWrap() {
        MemoryGuard guard;
        {
            SharedPointer<T> control = ghnew T();
            //control->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };

            control->MinSize = { 0, 0 };
            control->MaxSize = { 1000, 1000 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 0, 0 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 50, 70 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 150, 170 }, control->MeasuredSize);

            control->MinSize = { 0, 0 };
            control->MaxSize = { 10, 10 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 0, 0 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureContentWrap(std::function<FloatSize(T&)> initializer) {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = { Ghurund::UI::PreferredSize::Width::WRAP, Ghurund::UI::PreferredSize::Height::WRAP };
            FloatSize size = initializer(*control);
            if (control->Type.isOrExtends(Ghurund::UI::ControlGroup::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlGroup&)*control).Children.Size > 0);
            if (control->Type.isOrExtends(Ghurund::UI::ControlContainer::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlContainer&)*control).Child != nullptr);

            control->MinSize = { 0, 0 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 10, 10 };
            control->measure(size.Width + 20, size.Height + 20);
            Assert::AreEqual(size + FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 20, 20 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureEmptyFill() {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = { Ghurund::UI::PreferredSize::Width::FILL, Ghurund::UI::PreferredSize::Height::FILL };

            control->MinSize = { 0, 0 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 100, 120 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 100, 120 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 150, 170 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureContentFill(std::function<FloatSize(T&)> initializer) {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = { Ghurund::UI::PreferredSize::Width::FILL, Ghurund::UI::PreferredSize::Height::FILL };
            FloatSize size = initializer(*control);
            if (control->Type.isOrExtends(Ghurund::UI::ControlGroup::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlGroup&)*control).Children.Size > 0);
            if (control->Type.isOrExtends(Ghurund::UI::ControlContainer::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlContainer&)*control).Child != nullptr);

            control->MinSize = { 0, 0 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 10, 10 };
            control->measure(size.Width + 20, size.Height + 20);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 20, 20 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureEmptyPixels() {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::PIXELS, 20),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PIXELS, 30)
            //};

            control->MinSize = { 0, 0 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 20, 30 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 50, 70 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 150, 170 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureContentPixels(std::function<FloatSize(T&)> initializer) {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::PIXELS, 20),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PIXELS, 30)
            //};
            FloatSize size = initializer(*control);
            if (control->Type.isOrExtends(Ghurund::UI::ControlGroup::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlGroup&)*control).Children.Size > 0);
            if (control->Type.isOrExtends(Ghurund::UI::ControlContainer::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlContainer&)*control).Child != nullptr);

            control->MinSize = { 0, 0 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual({ 20,30 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 10, 10 };
            control->measure(size.Width + 20, size.Height + 20);
            Assert::AreEqual(size + FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 20, 20 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureEmptyPercent() {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::PERCENT, 25.0f),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PERCENT, 50.0f)
            //};

            control->MinSize = { 0, 0 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 25, 60 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 50, 70 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 150, 170 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureContentPercent(std::function<FloatSize(T&)> initializer) {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::PERCENT, 25.0f),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PERCENT, 50.0f)
            //};
            FloatSize size = initializer(*control);
            if (control->Type.isOrExtends(Ghurund::UI::ControlGroup::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlGroup&)*control).Children.Size > 0);
            if (control->Type.isOrExtends(Ghurund::UI::ControlContainer::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlContainer&)*control).Child != nullptr);

            control->MinSize = { 0, 0 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual({ (size.Width + 10) / 4.0f, (size.Height + 10) / 2.0f }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 10, 10 };
            control->measure(size.Width + 20, size.Height + 20);
            Assert::AreEqual(size + FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 20, 20 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureEmptyRatioWidth() {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::RATIO, 2.5f),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PIXELS, 50.0f)
            //};

            control->MinSize = { 0, 0 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 125, 50 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 125, 70 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 150, 170 }, control->MeasuredSize);

            control->MinSize = { 0, 0 };
            control->MaxSize = { 10, 10 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureContentRatioWidth(std::function<FloatSize(T&)> initializer) {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::RATIO, 2.5f),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::PIXELS, 50.0f)
            //};
            FloatSize size = initializer(*control);
            if (control->Type.isOrExtends(Ghurund::UI::ControlGroup::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlGroup&)*control).Children.Size > 0);
            if (control->Type.isOrExtends(Ghurund::UI::ControlContainer::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlContainer&)*control).Child != nullptr);

            control->MinSize = { 0, 0 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual({ (size.Width + 10) / 4.0f, (size.Height + 10) / 2.0f }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 10, 10 };
            control->measure(size.Width + 20, size.Height + 20);
            Assert::AreEqual(size + FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 20, 20 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureEmptyRatioHeight() {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::PIXELS, 25.0f),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::RATIO, 0.5f)
            //};

            control->MinSize = { 0, 0 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 25, 12.5f }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 50, 70 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 150, 170 }, control->MeasuredSize);

            control->MinSize = { 0, 0 };
            control->MaxSize = { 10, 10 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = { 50, 70 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = { 150, 170 };
            control->measure(100, 120);
            Assert::AreEqual(FloatSize{ 10, 10 }, control->MeasuredSize);
        }
    }

    template<class T>
    void measureContentRatioHeight(std::function<FloatSize(T&)> initializer) {
        MemoryGuard guard;
        {
            SharedPointer<T> control = new T();
            //control->PreferredSize = {
            //    Ghurund::UI::PreferredSize::Width(Ghurund::UI::PreferredSize::Type::PIXELS, 25.0f),
            //    Ghurund::UI::PreferredSize::Height(Ghurund::UI::PreferredSize::Type::RATIO, 0.5f)
            //};
            FloatSize size = initializer(*control);
            if (control->Type.isOrExtends(Ghurund::UI::ControlGroup::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlGroup&)*control).Children.Size > 0);
            if (control->Type.isOrExtends(Ghurund::UI::ControlContainer::TYPE))
                Assert::IsTrue(((Ghurund::UI::ControlContainer&)*control).Child != nullptr);

            control->MinSize = { 0, 0 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual({ (size.Width + 10) / 4.0f, (size.Height + 10) / 2.0f }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 10, 10 };
            control->measure(size.Width + 20, size.Height + 20);
            Assert::AreEqual(size + FloatSize{ 10, 10 }, control->MeasuredSize);

            control->MinSize = size + FloatSize{ 20, 20 };
            control->measure(size.Width + 10, size.Height + 10);
            Assert::AreEqual(size + FloatSize{ 20, 20 }, control->MeasuredSize);
        }
    }
}