#pragma once

#include "ui/adapter/AdapterLayout.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class ToolbarItemAdapter;

    class Toolbar: public Widget {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Toolbar::GET_TYPE();
#pragma endregion

    private:
        AdapterLayout* adapterLayout = nullptr;
        ToolbarItemAdapter* itemAdapter = nullptr;

        void updateProperties();

    protected:
        void onLayoutChanged();

    public:
        inline ToolbarItemAdapter& getItemAdapter() {
            return *itemAdapter;
        }

        inline void setItemAdapter(ToolbarItemAdapter& itemAdapter) {
            this->itemAdapter = &itemAdapter;
        }

        __declspec(property(get = getItemAdapter, put = setItemAdapter)) ToolbarItemAdapter& ItemAdapter;
    };
}