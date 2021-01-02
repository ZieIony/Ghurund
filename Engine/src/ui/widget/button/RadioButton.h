#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/style/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class RadioButton:public Widget<CheckBoxRadioLayout> {
    private:
        Event<RadioButton> onCheckedChanged = Event<RadioButton>(*this);

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(RadioButton))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef SharedPointer<RadioButton> RadioButtonPtr;

    class RadioTextButton:public RadioButton, public TextMixin {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(RadioTextButton))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        RadioTextButton(CheckBoxRadioTextLayout* layout = ghnew RadioTextButtonLayout()):RadioButton(layout) {
            textView = layout->TextBlock;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef SharedPointer<RadioTextButton> RadioTextButtonPtr;
}