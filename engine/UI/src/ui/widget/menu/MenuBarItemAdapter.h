#pragma once

#include "ui/adapter/ListItemAdapter.h"
#include "ui/widget/menu/MenuItem.h"
#include "core/object/SharedPointer.h"

namespace Ghurund::UI {
	class MenuBarItemAdapter:public ListItemAdapter<SharedPointer<MenuItem>> {
    private:
        ResourceManager& resourceManager;

    public:
        MenuBarItemAdapter(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual Control* makeControl(size_t type) const;

        virtual void bind(Control& control, size_t position) const override;
    };

}