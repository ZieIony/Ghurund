#pragma once

#include "ui/adapter/ListItemAdapter.h"
#include "ui/widget/menu/MenuItem.h"
#include "core/SharedPointer2.h"

namespace Ghurund::UI {
	class MenuBarItemAdapter:public ListItemAdapter<SharedPointer2<MenuItem>> {
    private:
        ResourceManager& resourceManager;

    public:
        MenuBarItemAdapter(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual Control* makeControl(size_t type) const;

        virtual void bind(Control& control, size_t position) const override;
    };

}