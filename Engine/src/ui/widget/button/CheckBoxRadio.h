#pragma once

#include "CheckBoxLayout.h"
#include "ui/control/SelectableView.h"
#include "ui/widget/ContentWidget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class CheckBoxRadio:public ContentWidget<CheckBoxLayout> {
    private:
        Event<CheckBoxRadio> onCheckedChanged = Event<CheckBoxRadio>(*this);

    protected:
        static const Ghurund::Type& GET_TYPE();

        EventHandler<Control> stateHandler = [this](Control& control) {
            if (Layout->Selectable->Pressed) {
                Layout->State->State = IndicatorState::PRESSED;
            } else if (Layout->Selectable->Focused || Layout->Selectable->Hovered) {
                Layout->State->State = IndicatorState::FOCUSED;
            } else {
                Layout->State->State = IndicatorState::NONE;
            }
            return true;
        };

        virtual void onLayoutChanged() override;

    public:
        inline void setChecked(bool checked) {
            Layout->Selectable->Selected = checked;
            onStateChanged();
        }

        inline bool isChecked() const {
            return Layout->Selectable->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        inline Event<CheckBoxRadio>& getCheckedChanged() {
            return onCheckedChanged;
        }

        __declspec(property(get = getCheckedChanged)) Event<CheckBoxRadio>& CheckedChanged;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class CheckBoxRadioStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}