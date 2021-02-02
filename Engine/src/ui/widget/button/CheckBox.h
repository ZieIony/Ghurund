#pragma once

#include "CheckBoxRadioLayout.h"
#include "ui/style/Style.h"
#include "ui/mixin/TextMixin.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class CheckBox:public Widget<CheckBoxLayout> {
    private:
        Event<CheckBox> onCheckedChanged = Event<CheckBox>(*this);

    protected:
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<CheckBox>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBox))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }
    
    public:
        CheckBox() {
            Focusable = true;
        }

        virtual void setLayout(CheckBoxLayout* layout) override {
            if (Layout) {
                Layout->SelectableView->OnStateChanged.clear();
                Layout->SelectableView->OnClicked.clear();
            }
            __super::setLayout(layout);
            if (layout) {
                layout->SelectableView->OnStateChanged.clear();
                layout->SelectableView->OnStateChanged.add(OnStateChanged);
                layout->SelectableView->OnClicked.clear();
                layout->SelectableView->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
                    Checked = !Checked;
                    onCheckedChanged();
                    return true;
                });
            }
        }

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

        virtual Status load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) override {
            Status result = __super::load(loader, context, xml);
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

    class CheckBoxText:public CheckBox, public TextMixin {
    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(CheckBoxText))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        CheckBoxText(CheckBoxRadioTextLayout* layout = ghnew TextCheckBoxLayout()):CheckBox() {
            //Layout = layout;
            textView = layout->TextBlock;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}