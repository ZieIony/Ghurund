#pragma once

#include "CheckBoxBinding.h"
#include "ui/control/SelectableView.h"
#include "ui/widget/Widget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    template<typename CheckBoxRadioType>
    class CheckBoxRadio:public Widget<CheckBoxBinding> {
    private:
        Event<CheckBoxRadioType> onCheckedChanged = Event<CheckBoxRadioType>((CheckBoxRadioType&)*this);

    protected:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBoxRadio>(NAMESPACE_NAME, GH_STRINGIFY(CheckBoxRadio))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

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

    public:
        inline void setChecked(bool checked) {
            Layout->Selectable->Selected = checked;
            onStateChanged();
        }

        inline bool isChecked() const {
            return Layout->Selectable->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        inline Event<CheckBoxRadioType>& getCheckedChanged() {
            return onCheckedChanged;
        }

        __declspec(property(get = getCheckedChanged)) Event<CheckBoxRadioType>& CheckedChanged;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            Status result = __super::load(loader, xml);
            if (result != Status::OK)
                return result;
            auto checkedAttr = xml.FindAttribute("checked");
            if (checkedAttr)
                Checked = checkedAttr->BoolValue();
            return Status::OK;
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class CheckBoxRadioStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}