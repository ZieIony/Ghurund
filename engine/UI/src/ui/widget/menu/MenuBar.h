#pragma once

#include "ui/adapter/AdapterLayout.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class MenuBarItemAdapter;

    class MenuBar: public Widget {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = MenuBar::GET_TYPE();
#pragma endregion

    private:
        AdapterLayout* adapterLayout = nullptr;
        MenuBarItemAdapter* itemAdapter = nullptr;

        void updateProperties();

    protected:
        void onLayoutChanged();

    public:
        inline MenuBarItemAdapter& getItemAdapter() {
            return *itemAdapter;
        }

        inline void setItemAdapter(MenuBarItemAdapter& itemAdapter) {
            this->itemAdapter = &itemAdapter;
        }

        __declspec(property(get = getItemAdapter, put = setItemAdapter)) MenuBarItemAdapter& ItemAdapter;
    };
}