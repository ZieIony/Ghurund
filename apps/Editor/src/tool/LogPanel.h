#pragma once

#include "LogRowBinding.h"
#include "LogPanelBinding.h"
#include "control/TitleBar.h"

#include "core/logging/Logger.h"
#include "ui/style/Theme.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ImageView.h"
#include "ui/image/Bitmap.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "ui/text/TextBlock.h"
#include "ui/widget/menu/Toolbar.h"

using namespace Ghurund;

namespace Ghurund::Editor {
    class LogRow:public Widget<LogRowBinding> {
    public:
        inline ImageDrawable* getImage() {
            return Layout->Icon->Image;
        }

        inline void setImage(ImageDrawable* image) {
            Layout->Icon->Image = image;
        }

        __declspec(property(get = getImage, put = setImage)) ImageDrawable* Image;

        const WString& getText() {
            return Layout->Text->Text;
        }

        void setText(const WString& text) {
            Layout->Text->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;
    };

    struct Log {
        LogType type;
        WString text;
    };

    class LogItemAdapter:public ItemAdapter<Log, LogRow> {
    private:
        Theme& theme;

    public:
        LogItemAdapter(Theme& theme):theme(theme) {}

        virtual LogRow* makeControl() const override {
            return ghnew LogRow();
        }

        virtual void bind(LogRow& control, Log& item, size_t position) const override {
            //logRow.Image = log->image;
            control.Text = item.text;
        }
    };

    class LogPanel:public Widget<LogPanelBinding> {
    private:
        Bitmap* sortIcon, * categoryIcon;

        List<Log> items;

        virtual void onLayoutChanged() override {
            /*//sortIcon = BitmapImage::makeFromImage(Context->Graphics, L"icons/sort 18.png");
            //categoryIcon = BitmapImage::makeFromImage(context, L"icons/category 18.png");
            Layout->Toolbar->Items = {
                   ghnew ButtonMenuItem(sortIcon, L"sort", [](Control&) {
                       Logger::log(LogType::INFO, "sort clicked\n");
                   }),
                   ghnew ButtonMenuItem(categoryIcon, L"category", [](Control&) {
                       Logger::log(LogType::INFO, "category clicked\n");
                   })
            };

            Layout->Recycler->LayoutManager = ghnew VerticalLayoutManager();
            auto provider = ghnew AdapterChildrenProvider<Log, LogRow>(*Layout->Recycler);
            provider->Adapters.add(ghnew LogItemAdapter(*Theme));
            provider->Items = ghnew ListItemSource<Log>(items);
            Layout->Recycler->childrenProvider = provider;*/
        }

    public:
        void addLog(LogType logType, const WString& message) {
            items.add({ logType, message });
            Layout->Recycler->invalidate();
        }
    };
}