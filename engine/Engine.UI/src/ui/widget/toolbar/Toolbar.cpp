#include "ghuipch.h"
#include "Toolbar.h"

#include "core/reflection/TypeBuilder.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Toolbar::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Toolbar>(NAMESPACE_NAME, GH_STRINGIFY(Toolbar))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    void Toolbar::onLayoutChanged() {
        __super::onLayoutChanged();
        Control* layoutControl = layout.get();
        if (layoutControl) {
            setPointer(adapterLayout, (Ghurund::UI::AdapterLayout*)layoutControl->find("adapterLayout"));
            if (adapterLayout) {
                //adapterLayout->ItemAdapter = std::make_unique<ToolbarItemAdapter>();
                //adapterLayout->LayoutManager = std::make_unique<HorizontalLayoutManager>();
            }
        }
    }
}
