#pragma once

#include "StringObject.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/VerticalScrollBar.h"

using namespace Ghurund;

class TestRecycler:public HorizontalLayout {
private:
    List<StringObject*> items;
    RecyclerView<StringObject*, Control>* recyclerView;
    VerticalScrollBar *scrollBar;

public:
    TestRecycler(Ghurund::UI::Theme& theme) {
        recyclerView = ghnew RecyclerView<StringObject*, Control>();
        recyclerView->PreferredSize.width = PreferredSize::Width::FILL;
        scrollBar = ghnew VerticalScrollBar(theme);
        scrollBar->Name = "recycler scroll";

        Gdiplus::Image* image = new Gdiplus::Image(L"images/game.png");
        items.addAll({
            ghnew StringObjectHeader("Character tests"),
            ghnew StringObjectItem("Foxy fox", "Jumps over big fence"),
            //ghnew StringObjectItem("Ósemka", _T("ążśćńę123-~,.;")),
            ghnew StringObjectItem("Strawberry", "Cherry and a rainbow"),
            ghnew StringObjectHeader("Fruits"),
            ghnew StringObjectItem("Melon", "Best fruit ever"),
            ghnew StringObjectItem("Blueberry", "Greenberry"),
            ghnew StringObjectItem("Watermelon", "Noice"),
            ghnew StringObjectItem("Apple", "Android"),
            ghnew StringObjectItem("Pear", "Deer"),
            ghnew StringObjectItem("Plum", "Splash"),
            ghnew StringObjectItem("Orange", "A color or a fruit?"),
            ghnew StringObjectItem("Banana", "Mana mana"),
            ghnew StringObjectItem("Beer", "Dark, with honey"),
            ghnew StringObjectItem("Lemon", "Tree")
            });
        recyclerView->LayoutManager = ghnew VerticalLayoutManager<StringObject*, Control>();
        recyclerView->Items = ghnew ListItemSource<StringObject*>(items);
        recyclerView->Adapters.addAll({
            ghnew StringHeaderAdapter(theme),
            ghnew StringItemAdapter(theme, image)
            });

        Children = { recyclerView, scrollBar };
    }

    ~TestRecycler() {
        items.deleteItems();
    }
};