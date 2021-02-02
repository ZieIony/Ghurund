#pragma once

#include "BoolPropertyRow.h"
#include "StringPropertyRow.h"
#include "PropertyRow.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/adapter/AdapterChildrenProvider.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Ghurund::UI {
    class PropertyList:public ControlContainer {
    private:
        RecyclerView* recycler;
        List<ObjectProperty*> items;
        Object* item = nullptr;

    public:
        PropertyList() {
            recycler = ghnew RecyclerView();
            recycler->LayoutManager = ghnew VerticalLayoutManager();
            auto provider = ghnew AdapterChildrenProvider<ObjectProperty*, PropertyRow>(*recycler);
            provider->Adapters = {
                ghnew BoolPropertyRowAdapter(),
                ghnew WStringPropertyRowAdapter(),
                ghnew AStringPropertyRowAdapter(),
                ghnew PropertyRowAdapter()
            };
            provider->Items = ghnew ListItemSource<ObjectProperty*>(items);
            recycler->childrenProvider = provider;
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

    typedef SharedPointer<PropertyList> PropertyListPtr;
}