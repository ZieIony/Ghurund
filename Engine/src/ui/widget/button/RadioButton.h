#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class RadioButton:public Widget2<CheckBoxRadioLayout> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(RadioButton);

        Event<RadioButton> onCheckedChanged = Event<RadioButton>(*this);

    public:
        RadioButton(CheckBoxRadioLayout* layout);

        inline void setChecked(bool checked) {
            Layout.SelectableView->Selected = checked;
        }

        inline bool isChecked() const {
            return Layout.SelectableView->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        Event<RadioButton>& getOnCheckedChanged() {
            return onCheckedChanged;
        }

        __declspec(property(get = getOnCheckedChanged)) Event<RadioButton>& OnCheckedChanged;

        inline static const Ghurund::Type& TYPE = TypeBuilder<RadioButton>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<RadioButton> RadioButtonPtr;

    class RadioTextButton:public RadioButton, public TextMixin {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(RadioTextButton);

    public:
        RadioTextButton(CheckBoxRadioTextLayout* layout):RadioButton(layout) {
            textView = layout->TextBlock;
        }

        RadioTextButton(Theme& theme):RadioTextButton(ghnew RadioTextButtonLayout(theme)) {}

        inline static const Ghurund::Type& TYPE = TypeBuilder<RadioTextButton>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<RadioTextButton> RadioTextButtonPtr;
}