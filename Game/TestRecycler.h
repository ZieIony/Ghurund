#pragma once

#include "ui/control/RecyclerView.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "ui/control/LinearLayout.h"
#include "ui/widget/VerticalScrollBar.h"

#include "StringObject.h"

using namespace Ghurund;

class TestRecycler:public HorizontalLayout {
private:
    List<StringObject*> items;
    RecyclerView<StringObject*, Control>* recyclerView;
    VerticalScrollBar *scrollBar;

public:
    TestRecycler(Theme& theme) {
        recyclerView = ghnew RecyclerView<StringObject*, Control>();
        scrollBar = ghnew VerticalScrollBar(ghnew VerticalScrollBarLayout(theme));
        scrollBar->Name = "recycler scroll";

        ImagePtr image = ghnew GdiImage(_T("images/game.png"));
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
        recyclerView->addAdapter(ghnew StringHeaderAdapter(theme));
        recyclerView->addAdapter(ghnew StringItemAdapter(theme, image));

        Children = { recyclerView, scrollBar };
    }

    ~TestRecycler() {
        items.deleteItems();
    }
};