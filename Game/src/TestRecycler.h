#pragma once

#include "StringObject.h"
#include "TestRowAdapter.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/layout/VerticalLayoutManager.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/VerticalScrollBar.h"

namespace Game {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class TestRecycler:public HorizontalLayout {
    private:
        List<StringObject*> items;
        RecyclerView* recyclerView;
        VerticalScrollBar* scrollBar;

    public:
        TestRecycler(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context, LayoutLoader& loader, Ghurund::UI::Theme& theme) {
            recyclerView = ghnew RecyclerView();
            recyclerView->PreferredSize.width = PreferredSize::Width::FILL;
            scrollBar = ghnew VerticalScrollBar();
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

            SharedPointer<BitmapImage> foxImage = BitmapImage::makeFromImage(context, L"images/test/fox.jpg");
            SharedPointer<BitmapImage> strawberryImage = BitmapImage::makeFromImage(context, L"images/test/strawberry.jpg");
            SharedPointer<BitmapImage> melonImage = BitmapImage::makeFromImage(context, L"images/test/melon.jpg");
            SharedPointer<BitmapImage> blueberryImage = BitmapImage::makeFromImage(context, L"images/test/blueberry.jpg");
            SharedPointer<BitmapImage> watermelonImage = BitmapImage::makeFromImage(context, L"images/test/watermelon.jpg");
            SharedPointer<BitmapImage> appleImage = BitmapImage::makeFromImage(context, L"images/test/apple.jpg");
            SharedPointer<BitmapImage> pearImage = BitmapImage::makeFromImage(context, L"images/test/pear.jpg");
            SharedPointer<BitmapImage> plumImage = BitmapImage::makeFromImage(context, L"images/test/plum.jpg");
            SharedPointer<BitmapImage> orangeImage = BitmapImage::makeFromImage(context, L"images/test/orange.jpg");
            SharedPointer<BitmapImage> bananaImage = BitmapImage::makeFromImage(context, L"images/test/banana.jpg");
            SharedPointer<BitmapImage> beerImage = BitmapImage::makeFromImage(context, L"images/test/beer.jpg");
            SharedPointer<BitmapImage> lemonImage = BitmapImage::makeFromImage(context, L"images/test/lemon.jpg");

            items = {
                ghnew StringObjectHeader(L"Character tests"),
                ghnew StringObjectItem(L"Foxy fox", L"Jumps over big fence", foxImage),
                //ghnew StringObjectItem(L"Ósemka", _T("ążśćńę123-~,.;")),
                ghnew StringObjectItem(L"Strawberry", L"Cherry and a rainbow", strawberryImage),
                ghnew StringObjectHeader(L"Fruits"),
                ghnew StringObjectItem(L"Melon", L"Best fruit ever", melonImage),
                ghnew StringObjectItem(L"Blueberry", L"Greenberry", blueberryImage),
                ghnew StringObjectItem(L"Watermelon", L"Noice", watermelonImage),
                ghnew StringObjectItem(L"Apple", L"Android", appleImage),
                ghnew StringObjectItem(L"Pear", L"Deer", pearImage),
                ghnew StringObjectItem(L"Plum", L"Splash", plumImage),
                ghnew StringObjectItem(L"Orange", L"A color or a fruit?", orangeImage),
                ghnew StringObjectItem(L"Banana", L"Mana mana", bananaImage),
                ghnew StringObjectItem(L"Beer", L"Dark, with honey", beerImage),
                ghnew StringObjectItem(L"Lemon", L"Tree", lemonImage)
            };
            recyclerView->LayoutManager = ghnew VerticalLayoutManager();
            auto provider = ghnew AdapterChildrenProvider<StringObject*, Control>(*recyclerView);
            provider->Adapters = {
                ghnew StringHeaderAdapter(theme),
                ghnew StringItemAdapter(context, loader, theme)
            };
            provider->Items = ghnew ListItemSource<StringObject*>(items);
            recyclerView->childrenProvider = provider;

            Children = { recyclerView, scrollBar };
        }

        ~TestRecycler() {
            items.deleteItems();
        }
    };
}
