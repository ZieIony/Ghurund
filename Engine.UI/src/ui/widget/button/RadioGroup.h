#pragma once

#include "RadioButton.h"

namespace Ghurund::UI {
    class RadioGroup {
    private:
        PointerList<RadioButton*> buttons;
        std::function<bool(RadioButton&)> checkedHandler = [this](RadioButton& sender) {
            for (auto b : buttons) {
                if (b != &sender)
                    b->Checked = false;
            }
            return true;
        };

    public:
        RadioGroup() {}

        RadioGroup(const std::initializer_list<RadioButton*>& buttons) {
            addAll(buttons);
        }

        inline void add(RadioButton* button) {
            buttons.add(button);
            button->CheckedChanged.add(checkedHandler);
        }

        inline void addAll(const std::initializer_list<RadioButton*>& buttons) {
            for (RadioButton* b : buttons) {
                this->buttons.add(b);
                b->CheckedChanged.add(checkedHandler);
            }
        }

        inline RadioGroup& operator=(const std::initializer_list<RadioButton*>& buttons) {
            clear();
            addAll(buttons);
            return *this;
        }

        inline void remove(RadioButton* button) {
            buttons.remove(button);
            button->CheckedChanged.clear();
        }

        inline void clear() {
            for (RadioButton* b : buttons)
                b->CheckedChanged.clear();
            buttons.clear();
        }
    };
}