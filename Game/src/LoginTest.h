#pragma once

#include "MusicPlayer.h"

#include "ui/control/ScrollView.h"
#include "ui/control/Space.h"
#include "ui/layout/StackLayout.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/textfield/TextField.h"
#include <ui/widget/button/TextButton.h>
#include <ui/drawable/BitmapImageDrawable.h>
#include <ui/drawable/SvgImageDrawable.h>

using namespace Ghurund;
using namespace Ghurund::UI;
using namespace Ghurund::Editor;

class TestLoginScreen:public StackLayout {
public:
    TestLoginScreen(Ghurund::UI::Theme& theme, ResourceContext& resourceContext) {
        Name = "login screen";
        Alignment = { Alignment::Horizontal::CENTER, Alignment::Vertical::CENTER };

        auto layout = makeShared<VerticalLayout>();
        layout->PreferredSize = { 300, PreferredSize::Height::WRAP };

        {
            auto imageView = makeShared<ImageView>();
            imageView->PreferredSize.height = 200.0f;
            imageView->Image = makeShared<BitmapImageDrawable>(BitmapImage::makeFromImage(resourceContext, "images/test/strawberry.jpg"));

            auto loginRow = makeShared<HorizontalLayout>();
            loginRow->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                auto loginIconView = makeShared<ImageView>();
                SharedPointer<SvgImage> faceIcon = resourceContext.ResourceManager.load<SvgImage>(resourceContext, "icons/face 24.svg");
                auto faceIconDrawable = makeShared<SvgImageDrawable>(faceIcon);
                faceIconDrawable->Tint = theme.ColorForegroundSecondaryOnBackground;
                loginIconView->Image = faceIconDrawable;
                auto loginTextField = makeShared<TextField>();

                loginRow->Children = {
                    makeShared<Space>(8),
                    loginIconView,
                    makeShared<Space>(16),
                    loginTextField,
                    makeShared<Space>(8)
                };
            }

            auto passwordRow = makeShared<HorizontalLayout>();
            passwordRow->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                auto passwordIconView = makeShared<ImageView>();
                SharedPointer<SvgImage> lockIcon = resourceContext.ResourceManager.load<SvgImage>(resourceContext, "icons/lock 24.svg");
                auto passwordIconDrawable = makeShared<SvgImageDrawable>(lockIcon);
                passwordIconDrawable->Tint = theme.ColorForegroundSecondaryOnBackground;
                passwordIconView->Image = passwordIconDrawable;
                auto passwordTextField = makeShared<TextField>();

                passwordRow->Children = {
                    makeShared<Space>(8),
                    passwordIconView,
                    makeShared<Space>(16),
                    passwordTextField,
                    makeShared<Space>(8)
                };
            }

            auto buttonsRow = makeShared<HorizontalLayout>();
            buttonsRow->PreferredSize.height = PreferredSize::Height::WRAP;
            {
                auto loginButton = makeShared<TextButton>();
                loginButton->PreferredSize.width = PreferredSize::Width::FILL;
                loginButton->Text = "LOGIN";
                auto registerButton = makeShared<TextButton>();
                registerButton->PreferredSize.width = PreferredSize::Width::FILL;
                registerButton->Text = "REGISTER";

                buttonsRow->Children = {
                    makeShared<Space>(8),
                    loginButton,
                    makeShared<Space>(16),
                    registerButton,
                    makeShared<Space>(8)
                };
            }

            layout->Children = {
                imageView,
                makeShared<Space>(8),
                loginRow,
                makeShared<Space>(8),
                passwordRow,
                makeShared<Space>(8),
                buttonsRow
            };
        }

        Children = { layout };
    }
};