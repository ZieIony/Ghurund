#pragma once

#include "ui/adapter/ListItemAdapter.h"
#include "ui/widget/menu/MenuItem.h"
#include "core/object/SharedPointer.h"

namespace Ghurund::UI {
	class ToolbarItemAdapter:public ListItemAdapter<SharedPointer<MenuItem>> {
    private:
        // borrowed
        ResourceManager* resourceManager;

    public:
        ToolbarItemAdapter(NotNull<ResourceManager> resourceManager):resourceManager(&resourceManager) {}

        virtual Control* makeControl(size_t type) const;

        virtual void bind(Control& control, size_t position) const override;
    };

}