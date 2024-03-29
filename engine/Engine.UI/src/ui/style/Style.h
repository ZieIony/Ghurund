#pragma once

namespace Ghurund::UI {
    class Control;

    class Style {
    public:
        virtual ~Style() = 0 {}

        virtual void onThemeChanged(Control& control) const {}

        virtual void onStateChanged(Control& control) const {}
    };

    template<class T>
    class TypedStyle:public Style {
    public:
        virtual void onThemeChanged(Control& control) const override {
            onThemeChanged((T&)control);
        }

        virtual void onStateChanged(Control& control) const override {
            onStateChanged((T&)control);
        }

        virtual void onThemeChanged(T& control) const {}

        virtual void onStateChanged(T& control) const {}
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Style>();
}