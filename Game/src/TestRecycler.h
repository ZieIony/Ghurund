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
    TestRecycler(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context, Ghurund::UI::Theme& theme) {
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

        ScopedPointer<BitmapImage> foxImage = BitmapImage::makeFromImage(context, L"images/test/fox.jpg");
        ScopedPointer<BitmapImage> strawberryImage = BitmapImage::makeFromImage(context, L"images/test/strawberry.jpg");
        ScopedPointer<BitmapImage> melonImage = BitmapImage::makeFromImage(context, L"images/test/melon.jpg");
        ScopedPointer<BitmapImage> blueberryImage = BitmapImage::makeFromImage(context, L"images/test/blueberry.jpg");
        ScopedPointer<BitmapImage> watermelonImage = BitmapImage::makeFromImage(context, L"images/test/watermelon.jpg");
        ScopedPointer<BitmapImage> appleImage = BitmapImage::makeFromImage(context, L"images/test/apple.jpg");
        ScopedPointer<BitmapImage> pearImage = BitmapImage::makeFromImage(context, L"images/test/pear.jpg");
        ScopedPointer<BitmapImage> plumImage = BitmapImage::makeFromImage(context, L"images/test/plum.jpg");
        ScopedPointer<BitmapImage> orangeImage = BitmapImage::makeFromImage(context, L"images/test/orange.jpg");
        ScopedPointer<BitmapImage> bananaImage = BitmapImage::makeFromImage(context, L"images/test/banana.jpg");
        ScopedPointer<BitmapImage> beerImage = BitmapImage::makeFromImage(context, L"images/test/beer.jpg");
        ScopedPointer<BitmapImage> lemonImage = BitmapImage::makeFromImage(context, L"images/test/lemon.jpg");

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
            ghnew StringItemAdapter(context, theme)
        };

        Children = { recyclerView, scrollBar };
    }

    ~TestRecycler() {
        items.deleteItems();
    }
};