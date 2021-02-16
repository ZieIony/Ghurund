#pragma once

#include "MusicPlayer.h"

#include "ui/control/ScrollView.h"
#include "ui/control/Space.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/text/TextField.h"
#include <ui/widget/button/Button.h>
#include <ui/drawable/BitmapImageDrawable.h>
#include <ui/drawable/SvgImageDrawable.h>

using namespace Ghurund;
using namespace Ghurund::UI;
using namespace Ghurund::Editor;

class TestLoginScreen:public StackLayout {
public:
    TestLoginScreen(Ghurund::UI::Theme& theme, Ghurund::ResourceContext& context, LayoutLoader& loader) {
        Name = "login screen";
        Alignment = { Alignment::Horizontal::CENTER, Alignment::Vertical::CENTER };

        auto layout = makeShared<VerticalLayout>();
        layout->PreferredSize = { 300, PreferredSize::Height::WRAP };

        {
            auto imageView = makeShared<ImageView>();
            imageView->PreferredSize.height = 200.0f;
            imageView->Image = makeShared<BitmapImageDrawable>(BitmapImage::makeFromImage(context, L"images/test/strawberry.jpg"));

            auto loginRow = makeShared<HorizontalLayout>();
            loginRow->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                auto loginIconView = makeShared<ImageView>();
                SharedPointer<SvgImage> faceIcon = context.ResourceManager.load<SvgImage>(context, L"icons/face 24.svg");
                auto faceIconDrawable = makeShared<SvgImageDrawable>(faceIcon);
                //faceIconDrawable->Tint = theme.ColorForegroundSecondaryOnBackground;
                loginIconView->Image = faceIconDrawable;
                auto loginTextField = makeShared<TextField>();

                loginRow->Children = {
                    makeShared<Space>(8.0f),
                    loginIconView,
                    makeShared<Space>(16.0f),
                    loginTextField,
                    makeShared<Space>(8.0f)
                };
            }

            auto passwordRow = makeShared<HorizontalLayout>();
            passwordRow->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                auto passwordIconView = makeShared<ImageView>();
                SharedPointer<SvgImage> lockIcon = context.ResourceManager.load<SvgImage>(context, L"icons/lock 24.svg");
                auto passwordIconDrawable = makeShared<SvgImageDrawable>(lockIcon);
                //passwordIconDrawable->Tint = theme.ColorForegroundSecondaryOnBackground;
                passwordIconView->Image = passwordIconDrawable;
                auto passwordTextField = makeShared<TextField>();

                passwordRow->Children = {
                    makeShared<Space>(8.0f),
                    passwordIconView,
                    makeShared<Space>(16.0f),
                    passwordTextField,
                    makeShared<Space>(8.0f)
                };
            }

            auto buttonsRow = makeShared<HorizontalLayout>();
            buttonsRow->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                /*auto loginButton = makeShared<Button>(ghnew ButtonLayout(loader));
                loginButton->PreferredSize.width = PreferredSize::Width::FILL;
                loginButton->Text = L"LOGIN";
                auto registerButton = makeShared<Button>(ghnew ButtonLayout(loader));
                registerButton->PreferredSize.width = PreferredSize::Width::FILL;
                registerButton->Text = L"REGISTER";

                buttonsRow->Children = {
                    makeShared<Space>(8.0f),
                    loginButton,
                    makeShared<Space>(16.0f),
                    registerButton,
                    makeShared<Space>(8.0f)
                };*/
            }

            layout->Children = {
                imageView,
                makeShared<Space>(8.0f),
                loginRow,
                makeShared<Space>(8.0f),
                passwordRow,
                makeShared<Space>(8.0f),
                buttonsRow
            };
        }

        Children = { layout };
    }
};