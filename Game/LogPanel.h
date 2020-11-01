#pragma once

#include "ui/Theme.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/TextBlock.h"
#include "ui/control/ImageView.h"
#include "ui/control/RecyclerView.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "TitleBar.h"

using namespace Ghurund;

namespace Ghurund::Editor {
    class LogRow:public HorizontalLayout {
    private:
        ScopedPointer<ImageView> icon;
        ScopedPointer<TextBlock> text;

    public:
        LogRow(Theme& theme) {
            icon = ghnew ImageView();
            text = ghnew TextBlock(theme.textViewPrimaryStyle);
            Children = { icon, text };
            PreferredSize.height = PreferredSize::Height::WRAP;
        }

        inline GdiImage* getImage() {
            return icon->Image;
        }

        inline void setImage(GdiImage* image) {
            icon->Image = image;
        }

        __declspec(property(get = getImage, put = setImage)) GdiImage* Image;

        String& getText() {
            return text->Text;
        }

        void setText(const String& text) {
            this->text->Text = text;
        }

        __declspec(property(get = getText, put = setText)) String& Text;
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
        ScopedPointer<TitleBar> titleBar;
        ScopedPointer<Toolbar> toolbar;
        ScopedPointer<RecyclerView<Log, LogRow>> logRecycler;

        List<Log> items;

    public:
        LogPanel(Theme& theme) {
            titleBar = ghnew TitleBar(theme);
            titleBar->Text = "Logs";
            toolbar = ghnew Toolbar(theme.toolbarStyle);
            logRecycler = ghnew RecyclerView<Log, LogRow>();
            logRecycler->LayoutManager = ghnew VerticalLayoutManager<Log, LogRow>();
            logRecycler->Items = ghnew ListItemSource<Log>(items);
            logRecycler->Adapters.add(ghnew LogItemAdapter(theme));
            Children = { titleBar, toolbar, logRecycler };
        }

        void addLog(LogType logType, const String& message) {
            items.add({ logType, message });
            logRecycler->invalidate();
        }
    };
}