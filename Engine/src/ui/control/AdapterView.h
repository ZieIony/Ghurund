#pragma once

#include "ControlGroup.h"
#include "ItemAdapter.h"
#include "ItemSource.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::UI {
    template<class T = void*, class ControlType = Control>
    class AdapterView :public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(AdapterView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<AdapterView>();

    protected:
        List<ItemAdapter<T, ControlType>*> adapters;
        ItemSource<T>* items = nullptr;
        AdapterLayoutManager<T, ControlType>* layoutManager = nullptr;

        inline ItemAdapter<T, ControlType>* findAdapter(size_t position) {
            for (auto a:adapters) {
                if (a->canHandleItem(items->get(position), position))
                    return a;
            }
            return nullptr;
        }

    public:
        ~AdapterView() {
            adapters.deleteItems();
            delete items;
            delete layoutManager;
        }

        inline ItemSource<T>* getItems() {
            return items;
        }

        inline void setItems(ItemSource<T>* items) {
            this->items = items;
        }

        __declspec(property(get = getItems, put = setItems)) ItemSource<T>* Items;

        inline AdapterLayoutManager<T, ControlType>* getLayoutManager() {
            return layoutManager;
        }

        inline void setLayoutManager(AdapterLayoutManager<T, ControlType>* layoutManager) {
            this->layoutManager = layoutManager;
        }

        __declspec(property(get = getLayoutManager, put = setLayoutManager)) AdapterLayoutManager<T, ControlType>* LayoutManager;

        inline List<ItemAdapter<T, ControlType>*>& getAdapters() {
            return adapters;
        }

        __declspec(property(get = getAdapters)) List<ItemAdapter<T, ControlType>*>& Adapters;

        virtual ControlType* getChild(size_t index) {
            ItemAdapter<T, ControlType>* adapter = findAdapter(index);
            ControlType* control = adapter->getControl();
            adapter->bind(*control, items->get(index), index);
            return control;
        }

        virtual void releaseChild(Control* control, size_t index) {
        }

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            if (layoutManager)
                measuredSize = layoutManager->measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (layoutManager)
                layoutManager->layout(*this, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<AdapterView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE());

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}