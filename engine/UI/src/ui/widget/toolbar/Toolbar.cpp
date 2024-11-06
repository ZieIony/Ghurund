#include "ghuipch.h"
#include "Toolbar.h"

#include "ToolbarItemAdapter.h"
#include "core/reflection/TypeBuilder.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Toolbar::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Toolbar>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    void Toolbar::updateProperties() {
        if (adapterLayout) {
            adapterLayout->ItemAdapter = *itemAdapter;
        }
    }

    void Toolbar::onLayoutChanged() {
        __super::onLayoutChanged();
        Control* layoutControl = layout.get();
        if (layoutControl) {
            setPointer(adapterLayout, (Ghurund::UI::AdapterLayout*)layoutControl->find("adapterLayout"));
            updateProperties();
            if (adapterLayout) {
                adapterLayout->LayoutManager = std::make_unique<HorizontalLayoutManager>();
            }
        }
    }
}
