#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class CheckBox:public Widget2<CheckBoxRadioLayout> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(CheckBox);

    public:
        CheckBox(CheckBoxRadioLayout* layout);

        inline void setChecked(bool checked) {
            Layout.SelectableView->Selected = checked;
        }

        inline bool isChecked() const {
            return Layout.SelectableView->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        inline static const Ghurund::Type& TYPE = TypeBuilder<CheckBox>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<CheckBox> CheckBoxPtr;

    class CheckBoxText:public CheckBox, public TextMixin {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(CheckBoxText);

    public:
        CheckBoxText(CheckBoxRadioTextLayout* layout):CheckBox(layout) {
            textView = layout->TextView;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<CheckBoxText>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<CheckBoxText> CheckBoxTextPtr;
}