#pragma once

#include "core/SharedPointer.h"
#include "core/string/String.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/Clip.h"
#include "ui/control/ColorView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/TextBlock.h"
#include "ui/drawable/BitmapImageDrawable.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/button/Button.h"
#include "ui/style/Theme.h"
#include "TestRowBinding.h"

namespace Game {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class TestRow:public Widget<TestRowBinding> {
    public:
        inline void bind(const StringObjectItem* data) {
            Layout->bind(data);
        }
    };

    class StringItemAdapter:public ItemAdapter<StringObject*, Control> {
    private:
        Theme& theme;
        ResourceContext& context;
        LayoutLoader& loader;

    public:
        StringItemAdapter(ResourceContext& context, LayoutLoader& loader, Theme& theme):context(context), loader(loader), theme(theme) {}

        virtual bool canHandleItem(StringObject* const& item, size_t position) const override {
            return item->type == StringObjectType::ITEM;
        }

        virtual Control* makeControl() const override {
            PointerList<Control*> controls;
            if (loader.load(L"file://Game/res/TestRow.xml", controls) == Status::OK) {
                auto row = ghnew TestRow();
                row->Layout = std::unique_ptr<TestRowBinding>(ghnew TestRowBinding(controls[0]));
            }
            return nullptr;
        }

        virtual void bind(Control& control, StringObject* const& item, size_t position) const override {
            TestRow& sor = (TestRow&)control;
            StringObjectItem* strObj = (StringObjectItem*)item;
            sor.bind(strObj);
        }
    };
}
