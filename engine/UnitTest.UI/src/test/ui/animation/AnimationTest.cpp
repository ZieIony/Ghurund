#include "pch.h"
#include "CppUnitTest.h"

#include "ui/animation/Animator.h"
#include "ui/animation/Animation.h"
#include <ui/Color.h>
#include "core/string/String.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::UI;

    TEST_CLASS(AnimationTest) {
public:
    TEST_METHOD(Animation) {
        Color color;
        Animator animator;
        ValueAnimation<Color> animation;

        animation.Duration = 200;
        animation.InitialValue = 0xffff0000;
        animation.TargetValue = 0xff00ff00;

        Assert::AreEqual(Color(0x00000000), color);
        Assert::IsFalse(animator.Running);

        animator.start(animation, color);
        animator.update(0);
        Assert::AreEqual(Color(0xffff0000), color);
        Assert::IsTrue(animator.Running);

        animator.update(100);
        Assert::AreEqual(Color(0xff7f7f00), color);
        Assert::IsTrue(animator.Running);

        animator.update(200);
        Assert::AreEqual(Color(0xff00ff00), color);
        Assert::IsFalse(animator.Running);

        animator.update(300);
        Assert::AreEqual(Color(0xff00ff00), color);
        Assert::IsFalse(animator.Running);
    }
    };
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString(const Ghurund::UI::Color& t) {
        return std::wstring(Ghurund::UI::toString(t).Data);
    }
}
