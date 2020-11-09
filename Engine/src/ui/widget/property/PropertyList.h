#pragma once

#include "BoolPropertyRow.h"
#include "StringPropertyRow.h"
#include "PropertyRow.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Ghurund::UI {
    class PropertyList:public ControlContainer {
    private:
        RecyclerView<ObjectProperty*, PropertyRow>* recycler;
        List<ObjectProperty*> items;
        Object* item = nullptr;

    public:
        PropertyList(Theme& theme) {
            recycler = ghnew RecyclerView<ObjectProperty*, PropertyRow>();
            recycler->LayoutManager = ghnew VerticalLayoutManager<ObjectProperty*, PropertyRow>();
            recycler->Adapters.addAll({
                ghnew BoolPropertyRowAdapter(theme),
                ghnew StringPropertyRowAdapter(theme),
                ghnew PropertyRowAdapter(theme)
                });
            recycler->Items = ghnew ListItemSource<ObjectProperty*>(items);
            Child = recycler;
        }

        ~PropertyList() {
            recycler->release();
        }

        inline Object* getItem() {
            return item;
        }

        inline void setItem(Object* item) {
            items.clear();
            if (item) {
                Ghurund::Type* type = (Ghurund::Type*)&item->Type;
                while (true) {
                    for (Property* p : type->Properties)
                        items.add(ghnew ObjectProperty(*item, *p));
                    if (!type->Supertype)
                        break;
                    type = (Ghurund::Type*)type->Supertype;
                }
            }
            this->item = item;
        }

        __declspec(property(get = getItem, put = setItem)) Object* Item;
    };

    typedef ScopedPointer<PropertyList> PropertyListPtr;
}