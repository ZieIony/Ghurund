#pragma once

#include "Theme.h"
#include "resource/ResourceManager.h"
#include "ui/font/TextFormat.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    class BaseTheme:public Ghurund::UI::Theme {
    public:
        BaseTheme(Ghurund::ResourceContext& context) {
            auto buttonFont = Ghurund::makeShared<Ghurund::UI::TextFormat>(L"fonts/lato_medium.ttf", L"Lato Medium", 10.0f, FW_MEDIUM, false);
            buttonFont->init(context.Graphics2D);
            TextFormats.set(Theme::TEXTFORMAT_BUTTON, buttonFont);

            auto listHeaderFont = Ghurund::makeShared<Ghurund::UI::TextFormat>(L"fonts/lato_light.ttf", L"Lato Light", 14.0f, FW_LIGHT, false);
            listHeaderFont->init(context.Graphics2D);
            TextFormats.set(Theme::TEXTFORMAT_LIST_HEADER, listHeaderFont);

            auto textPrimaryFont = Ghurund::makeShared<Ghurund::UI::TextFormat>(L"fonts/lato_regular.ttf", L"Lato", 11.0f, FW_REGULAR, false);
            textPrimaryFont->init(context.Graphics2D);
            TextFormats.set(Theme::TEXTFORMAT_TEXT_PRIMARY, textPrimaryFont);

            auto textSecondaryFont = Ghurund::makeShared<Ghurund::UI::TextFormat>(L"fonts/lato_regular.ttf", L"Lato", 10.0f, FW_REGULAR, false);
            textSecondaryFont->init(context.Graphics2D);
            TextFormats.set(Theme::TEXTFORMAT_TEXT_SECONDARY, textSecondaryFont);

            SharedPointer<BitmapImage> checkBoxChecked = BitmapImage::makeFromImage(context, L"icons/checkbox checked 18.png");
            Images.set(Theme::IMAGE_CHECKBOX_CHECKED, checkBoxChecked);
            SharedPointer<BitmapImage> checkBoxUnchecked = BitmapImage::makeFromImage(context, L"icons/checkbox unchecked 18.png");
            Images.set(Theme::IMAGE_CHECKBOX_UNCHECKED, checkBoxUnchecked);
            SharedPointer<BitmapImage> radioButtonChecked = BitmapImage::makeFromImage(context, L"icons/radiobutton checked 18.png");
            Images.set(Theme::IMAGE_RADIOBUTTON_CHECKED, radioButtonChecked);
            SharedPointer<BitmapImage> radioButtonUnchecked = BitmapImage::makeFromImage(context, L"icons/radiobutton unchecked 18.png");
            Images.set(Theme::IMAGE_RADIOBUTTON_UNCHECKED, radioButtonUnchecked);
            SharedPointer<BitmapImage> arrowUp = BitmapImage::makeFromImage(context, L"icons/arrow up 18.png");
            Images.set(Theme::IMAGE_ARROWUP, arrowUp);
            SharedPointer<BitmapImage> arrowDown = BitmapImage::makeFromImage(context, L"icons/arrow down 18.png");
            Images.set(Theme::IMAGE_ARROWDOWN, arrowDown);
        }
    };
}