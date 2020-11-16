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
    VerticalScrollBar* scrollBar;

public:
    TestRecycler(Ghurund::UI::Theme& theme) {
        recyclerView = ghnew RecyclerView<StringObject*, Control>();
        recyclerView->PreferredSize.width = PreferredSize::Width::FILL;
        scrollBar = ghnew VerticalScrollBar(theme);
        scrollBar->Name = "recycler scroll";
        scrollBar->OnScrolled.add([this](Control& control) {
            recyclerView->Scroll = { 0.0f, scrollBar->Scroll };
            recyclerView->repaint();
            return true;
        });
        recyclerView->OnScrolled.add([this](Control& control) {
            scrollBar->Scroll = recyclerView->Scroll.y;
            scrollBar->repaint();
            return true;
        });
        recyclerView->OnSizeChanged.add([this](Control& control) {
            scrollBar->MaxScroll = recyclerView->MaxScroll.y;
            scrollBar->repaint();
            return true;
        });

        ScopedPointer<BitmapImage> foxImage = ghnew BitmapImage(L"images/test/fox.jpg");
        ScopedPointer<BitmapImage> strawberryImage = ghnew BitmapImage(L"images/test/strawberry.jpg");
        ScopedPointer<BitmapImage> melonImage = ghnew BitmapImage(L"images/test/melon.jpg");
        ScopedPointer<BitmapImage> blueberryImage = ghnew BitmapImage(L"images/test/blueberry.jpg");
        ScopedPointer<BitmapImage> watermelonImage = ghnew BitmapImage(L"images/test/watermelon.jpg");
        ScopedPointer<BitmapImage> appleImage = ghnew BitmapImage(L"images/test/apple.jpg");
        ScopedPointer<BitmapImage> pearImage = ghnew BitmapImage(L"images/test/pear.jpg");
        ScopedPointer<BitmapImage> plumImage = ghnew BitmapImage(L"images/test/plum.jpg");
        ScopedPointer<BitmapImage> orangeImage = ghnew BitmapImage(L"images/test/orange.jpg");
        ScopedPointer<BitmapImage> bananaImage = ghnew BitmapImage(L"images/test/banana.jpg");
        ScopedPointer<BitmapImage> beerImage = ghnew BitmapImage(L"images/test/beer.jpg");
        ScopedPointer<BitmapImage> lemonImage = ghnew BitmapImage(L"images/test/lemon.jpg");

        items = {
            ghnew StringObjectHeader("Character tests"),
            ghnew StringObjectItem("Foxy fox", "Jumps over big fence", foxImage),
            //ghnew StringObjectItem("Ósemka", _T("ążśćńę123-~,.;")),
            ghnew StringObjectItem("Strawberry", "Cherry and a rainbow", strawberryImage),
            ghnew StringObjectHeader("Fruits"),
            ghnew StringObjectItem("Melon", "Best fruit ever", melonImage),
            ghnew StringObjectItem("Blueberry", "Greenberry", blueberryImage),
            ghnew StringObjectItem("Watermelon", "Noice", watermelonImage),
            ghnew StringObjectItem("Apple", "Android", appleImage),
            ghnew StringObjectItem("Pear", "Deer", pearImage),
            ghnew StringObjectItem("Plum", "Splash", plumImage),
            ghnew StringObjectItem("Orange", "A color or a fruit?", orangeImage),
            ghnew StringObjectItem("Banana", "Mana mana", bananaImage),
            ghnew StringObjectItem("Beer", "Dark, with honey", beerImage),
            ghnew StringObjectItem("Lemon", "Tree", lemonImage)
        };
        recyclerView->LayoutManager = ghnew VerticalLayoutManager();
        recyclerView->Items = ghnew ListItemSource<StringObject*>(items);
        recyclerView->Adapters = {
            ghnew StringHeaderAdapter(theme),
            ghnew StringItemAdapter(theme)
        };

        Children = { recyclerView, scrollBar };
    }

    ~TestRecycler() {
        items.deleteItems();
    }
};