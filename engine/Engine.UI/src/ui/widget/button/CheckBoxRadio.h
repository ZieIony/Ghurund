#pragma once

#include "ui/control/SelectableView.h"
#include "ui/control/DrawableView.h"
#include "ui/widget/Widget.h"
#include "ui/widget/StateIndicator.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
    template<typename CheckBoxRadioType>
    class CheckBoxRadio:public Widget {
    protected:
        Ghurund::UI::SelectableView* selectable = nullptr;
        Ghurund::UI::StateIndicator* state = nullptr;
        Ghurund::UI::DrawableView* drawable = nullptr;

        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBoxRadio>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(CheckBoxRadio))
                .withModifiers(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        EventHandler<Control> stateHandler = [this](Control& control) {
            if (selectable->Pressed) {
                state->State = IndicatorState::PRESSED;
            } else if (selectable->Focused || selectable->Hovered) {
                state->State = IndicatorState::FOCUSED;
            } else {
                state->State = IndicatorState::NONE;
            }
            return true;
        };

        virtual void bind() override {
            __super::bind();
            selectable = (Ghurund::UI::SelectableView*)find("selectable");
            state = (Ghurund::UI::StateIndicator*)find("state");
            drawable = (Ghurund::UI::DrawableView*)find("drawable");
        }

    public:
        Event<CheckBoxRadioType> checkedChanged = Event<CheckBoxRadioType>((CheckBoxRadioType&)*this);
  
        inline void setChecked(bool checked) {
            //selectable->Selected = checked;
            onStateChanged();
        }

        inline bool isChecked() const {
            return false;// selectable->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            __super::load(loader, xml);
            auto checkedAttr = xml.FindAttribute("checked");
            if (checkedAttr)
                Checked = checkedAttr->BoolValue();
        }

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    class CheckBoxRadioStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}