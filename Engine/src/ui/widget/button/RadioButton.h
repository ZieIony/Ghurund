#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/style/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class RadioButton:public Widget<CheckBoxRadioLayout> {
    private:
        Event<RadioButton> onCheckedChanged = Event<RadioButton>(*this);

    protected:
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<RadioButton>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(RadioButton))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void onLayoutChanged() override;

    public:
        RadioButton() {
            Focusable = true;
        }

        inline void setChecked(bool checked) {
            Layout->SelectableView->Selected = checked;
        }

        inline bool isChecked() const {
            return Layout->SelectableView->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        Event<RadioButton>& getOnCheckedChanged() {
            return onCheckedChanged;
        }

        __declspec(property(get = getOnCheckedChanged)) Event<RadioButton>& OnCheckedChanged;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override {
            Status result = __super::load(loader, xml);
            if (result != Status::OK)
                return result;
            auto checkedAttr = xml.FindAttribute("checked");
            if (checkedAttr)
                Checked = checkedAttr->BoolValue();
            return Status::OK;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}