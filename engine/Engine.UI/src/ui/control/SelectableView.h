#pragma once

#include "ClickableControl.h"

namespace Ghurund::UI {
    class SelectableView:public ClickableControl {
    private:
        bool selected = false;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
        
        inline bool isSelected() const {
            return selected;
        }

        inline void setSelected(bool selected) {
            this->selected = selected;
            onStateChanged();
        }

        __declspec(property(get = isSelected, put = setSelected)) bool Selected;

    private:
        //inline static const TypeProperty& SELECTED = TypedProperty<SelectableView, bool>(
         //   GH_STRINGIFY(bool), "selected", &isSelected, &setSelected);
    };
}