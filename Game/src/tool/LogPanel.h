#pragma once

#include "control/TitleBar.h"

#include "ui/Theme.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ImageView.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "ui/widget/menu/Toolbar.h"

using namespace Ghurund;

namespace Ghurund::Editor {
    class LogRow:public HorizontalLayout {
    private:
        SharedPointer<ImageView> icon;
        SharedPointer<TextBlock> text;

    public:
        LogRow(Theme& theme) {
            icon = ghnew ImageView();
            text = ghnew TextBlock(theme.textViewPrimaryStyle);
            Children = { icon, text };
            PreferredSize.height = PreferredSize::Height::WRAP;
        }

        inline BitmapImage* getImage() {
            return icon->Image;
        }

        inline void setImage(BitmapImage* image) {
            icon->Image = image;
        }

        __declspec(property(get = getImage, put = setImage)) BitmapImage* Image;

        UnicodeString& getText() {
            return text->Text;
        }

        void setText(const UnicodeString& text) {
            this->text->Text = text;
        }

        __declspec(property(get = getText, put = setText)) UnicodeString& Text;
    };

    struct Log {
        LogType type;
        String text;
    };

    class LogItemAdapter:public ItemAdapter<Log, LogRow> {
    private:
        Theme& theme;

    public:
        LogItemAdapter(Theme& theme):theme(theme) {}

        virtual LogRow* makeControl() const override {
            return ghnew LogRow(theme);
        }

        virtual void bind(LogRow& control, const Log& item, size_t position) const override {
            //logRow.Image = log->image;
            control.Text = item.text;
        }
    };

    class LogPanel:public VerticalLayout {
    private:
        SharedPointer<Toolbar> toolbar;
        SharedPointer<RecyclerView<Log, LogRow>> logRecycler;
        BitmapImage* sortIcon, * categoryIcon;

        List<Log> items;

    public:
        LogPanel(ResourceContext& context, Ghurund::UI::Theme& theme) {
            toolbar = ghnew Toolbar(theme);
            sortIcon = BitmapImage::makeFromImage(context, L"icons/sort 18.png");
            categoryIcon = BitmapImage::makeFromImage(context, L"icons/category 18.png");
            toolbar->Items = {
                   ghnew ButtonMenuItem(sortIcon, "sort", [](Control&) {
                       Logger::log(LogType::INFO, "sort clicked\n");
                   }),
                   ghnew ButtonMenuItem(categoryIcon, "category", [](Control&) {
                       Logger::log(LogType::INFO, "category clicked\n");
                   })
            };
            logRecycler = ghnew RecyclerView<Log, LogRow>();
            logRecycler->LayoutManager = ghnew VerticalLayoutManager();
            logRecycler->Items = ghnew ListItemSource<Log>(items);
            logRecycler->Adapters.add(ghnew LogItemAdapter(theme));
            Children = { toolbar, logRecycler };
        }

        void addLog(LogType logType, const String& message) {
            items.add({ logType, message });
            logRecycler->invalidate();
        }
    };
}