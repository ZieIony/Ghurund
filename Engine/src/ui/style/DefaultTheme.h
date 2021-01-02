#pragma once

#include "Theme.h"
#include "resource/ResourceManager.h"
#include "ui/font/TextStyle.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    class DefaultTheme:public Ghurund::UI::Theme {
    public:
        DefaultTheme(Ghurund::ResourceManager& resourceManager, Ghurund::ResourceContext& context) {
            auto buttonFont = Ghurund::makeShared<Ghurund::UI::TextStyle>(L"fonts/lato_medium.ttf", L"Lato Medium", 10.0f, FW_MEDIUM, false);
            buttonFont->init(context.Graphics2D);
            TextStyles.set(Theme::TEXTSTYLE_BUTTON, buttonFont);

            auto listHeaderFont = Ghurund::makeShared<Ghurund::UI::TextStyle>(L"fonts/lato_light.ttf", L"Lato Light", 14.0f, FW_LIGHT, false);
            listHeaderFont->init(context.Graphics2D);
            TextStyles.set(Theme::TEXTSTYLE_LIST_HEADER, listHeaderFont);

            auto textPrimaryFont = Ghurund::makeShared<Ghurund::UI::TextStyle>(L"fonts/lato_regular.ttf", L"Lato", 11.0f, FW_REGULAR, false);
            textPrimaryFont->init(context.Graphics2D);
            TextStyles.set(Theme::TEXTSTYLE_TEXT_PRIMARY, textPrimaryFont);

            auto textSecondaryFont = Ghurund::makeShared<Ghurund::UI::TextStyle>(L"fonts/lato_regular.ttf", L"Lato", 10.0f, FW_REGULAR, false);
            textSecondaryFont->init(context.Graphics2D);
            TextStyles.set(Theme::TEXTSTYLE_TEXT_SECONDARY, textSecondaryFont);

            checkBoxChecked = BitmapImage::makeFromImage(context, L"icons/checkbox checked 18.png");
            checkBoxUnchecked = BitmapImage::makeFromImage(context, L"icons/checkbox unchecked 18.png");
            radioButtonChecked = BitmapImage::makeFromImage(context, L"icons/radiobutton checked 18.png");
            radioButtonUnchecked = BitmapImage::makeFromImage(context, L"icons/radiobutton unchecked 18.png");
            arrowDown = BitmapImage::makeFromImage(context, L"icons/arrow down 18.png");
            arrowUp = BitmapImage::makeFromImage(context, L"icons/arrow up 18.png");
        }
    };
}