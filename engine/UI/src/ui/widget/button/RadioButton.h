#pragma once

#include "CheckBoxRadio.h"

namespace Ghurund::UI {
    class RadioButton:public CheckBoxRadio<RadioButton> {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = RadioButton::GET_TYPE();
#pragma endregion

    protected:
        virtual void onStateChanged() override;

    public:
        RadioButton() {
            interactionHandler.clicked += [this](InteractionHandler&, const MouseClickedEventArgs&) {
                Checked = checked;
                return true;
            };
        }
    };
}