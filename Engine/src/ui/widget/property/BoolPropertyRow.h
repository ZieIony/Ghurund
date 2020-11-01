#pragma once

#include "PropertyRow.h"
#include "ui/widget/button/CheckBox.h"

namespace Ghurund::UI {
    class BoolPropertyRow: public PropertyRow {
    private:
        CheckBoxPtr checkBox;

    public:
        BoolPropertyRow(Theme& theme):PropertyRow(theme) {
            HorizontalLayoutPtr horizontalLayout = ghnew HorizontalLayout();
            horizontalLayout->PreferredSize.height = PreferredSize::Height::WRAP;
            checkBox = ghnew CheckBox(ghnew CheckBoxLayout(theme));
            checkBox->OnCheckedChanged.add([this](CheckBox& checkBox) {
                return OnValueChanged();
            });
            horizontalLayout->Children = { checkBox };
            Content = horizontalLayout;
        }

        inline bool getValue() {
            return checkBox->Checked;
        }

        inline void setValue(bool selected) {
            checkBox->Checked = selected;
        }

        __declspec(property(get = getValue, put = setValue)) bool Value;
    };

    class BoolPropertyRowAdapter:public ItemAdapter<ObjectProperty*, PropertyRow> {
    private:
        Theme& theme;

    public:
        BoolPropertyRowAdapter(Theme& theme):theme(theme) {}

        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return S("bool") == item->Property.TypeName;
        }

        virtual PropertyRow* makeControl() const override {
            return ghnew BoolPropertyRow(theme);
        }

        virtual void bind(PropertyRow& control, ObjectProperty* const& item, size_t position) const override {
            control.Label = item->Property.Name;
            bool b;
            item->get((void**)&b);
            ((BoolPropertyRow&)control).Value = b;
            control.Content->Enabled = !item->Property.ReadOnly;
            control.OnValueChanged.clear();
            if (!item->Property.ReadOnly) {
                control.OnValueChanged.add([item](PropertyRow& row) {
                    bool b = ((BoolPropertyRow&)row).Value;
                    item->set((void*)b);
                    row.repaint();
                    return true;
                });
            }
        }
    };
}