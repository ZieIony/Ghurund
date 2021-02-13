#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/style/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class CheckBox:public ContentWidget<CheckBoxLayout> {
    private:
        Event<CheckBox> onCheckedChanged = Event<CheckBox>(*this);

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<CheckBox>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void onLayoutChanged() override;

    public:
        inline void setChecked(bool checked) {
            Layout->SelectableView->Selected = checked;
        }

        inline bool isChecked() const {
            return Layout->SelectableView->Selected;
        }

        __declspec(property(get = isChecked, put = setChecked)) bool Checked;

        inline Event<CheckBox>& getOnCheckedChanged() {
            return onCheckedChanged;
        }

        __declspec(property(get = getOnCheckedChanged)) Event<CheckBox>& OnCheckedChanged;

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