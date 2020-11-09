#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class CheckBox:public Widget<CheckBoxRadioLayout> {
    private:
        Event<CheckBox> onCheckedChanged = Event<CheckBox>(*this);

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
                .withSupertype(__super::TYPE);

            return TYPE;
        }
    
    public:
        CheckBox(CheckBoxRadioLayout* layout);

        inline void setChecked(bool checked) {
            Layout.SelectableView->Selected = checked;
        }

        inline bool isChecked() const {
            return Layout.SelectableView->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        inline Event<CheckBox>& getOnCheckedChanged() {
            return onCheckedChanged;
        }

        __declspec(property(get = getOnCheckedChanged)) Event<CheckBox>& OnCheckedChanged;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<CheckBox> CheckBoxPtr;

    class CheckBoxText:public CheckBox, public TextMixin {
    private:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBoxText))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        CheckBoxText(CheckBoxRadioTextLayout* layout):CheckBox(layout) {
            textView = layout->TextBlock;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<CheckBoxText> CheckBoxTextPtr;
}