#pragma once

#include "TestRecyclerBinding.h"
#include "ui/widget/Widget.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/adapter/AdapterChildrenProvider.h"
#include <TestRowBinding.h>

namespace Demo {
    using namespace Bindings;
    using namespace Ghurund::UI;

    struct TestItem {
        WString Text;
        WString Subtext;
        ImageDrawable* Image = nullptr;

        TestItem() {}

        TestItem(WString Text, WString Subtext, ImageDrawable* Image = nullptr) {
            this->Text = Text;
            this->Subtext = Subtext;
            if (Image) {
                Image->addReference();
                this->Image = Image;
            }
        }

        TestItem(const TestItem& item) {
            Text = item.Text;
            Subtext = item.Subtext;
            if (item.Image) {
                item.Image->addReference();
                Image = item.Image;
            }
        }

        ~TestItem() {
            if (Image)
                Image->release();
        }
    };

    typedef BindingWidget<TestItem, TestRowBinding<TestItem>> TestRow;

    typedef SingleAdapterChildrenProvider<TestItem, TestRow, BindingControlItemAdapter<TestItem, TestRow>> TestAdapterChildrenProvider;

    class TestRecycler:public Widget<TestRecyclerBinding> {
    private:

    protected:
        virtual void onLayoutChanged() override {
            if (!Layout)
                return;
            Layout->Recycler->LayoutManager = std::unique_ptr<VerticalLayoutManager>(ghnew VerticalLayoutManager());
            auto childrenProvider = ghnew TestAdapterChildrenProvider();
            Layout->Recycler->ChildrenProvider = std::unique_ptr<TestAdapterChildrenProvider>(childrenProvider);

            childrenProvider->ItemSource.Items.addAll({
                TestItem(L"Strawberry",L"Berry tasty",nullptr)
                });
        }

    public:

    };
}