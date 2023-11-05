#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class RadioButton:public CheckBoxRadio<RadioButton> {
    protected:
        virtual void onLayoutChanged() override;

        virtual void onStateChanged() override;

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}