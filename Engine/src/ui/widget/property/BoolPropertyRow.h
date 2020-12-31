#pragma once

#include "PropertyRow.h"
#include "ui/widget/button/CheckBox.h"

namespace Ghurund::UI {
    class BoolPropertyRow: public PropertyRow {
    private:
        SharedPointer<CheckBox> checkBox;

    public:
        BoolPropertyRow() {
            SharedPointer<HorizontalLayout> horizontalLayout = ghnew HorizontalLayout();
            horizontalLayout->PreferredSize.height = PreferredSize::Height::WRAP;
            checkBox = ghnew CheckBox();
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
    public:
        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return strcmp("bool", item->Property.TypeName) == 0;
        }

        virtual BoolPropertyRow* makeControl() const override {
            return ghnew BoolPropertyRow();
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