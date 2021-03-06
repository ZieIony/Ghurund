#pragma once

#include "audio/Sound.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/button/Button.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class MusicPlayer:public VerticalLayout {
    private:
        SharedPointer<ProgressBar> progressBar;
        SharedPointer<Button> playButton;
        SharedPointer<Button> stopButton;
        SharedPointer<Audio::Sound> sound;

    public:
        MusicPlayer(Ghurund::UI::Theme& theme) {
            PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
            progressBar = ghnew ProgressBar();
            progressBar->Style = theme.Styles[Theme::STYLE_PROGRESSBAR];
//            auto playIcon = makeShared<BitmapImage>("icons/play 18.png");
            playButton = ghnew Button();
         //   playButton->Image = playIcon;
       //     auto stopIcon = makeShared<BitmapImage>("icons/stop 18.png");
            stopButton = ghnew Button();
        //    stopButton->Image = stopIcon;
            SharedPointer<HorizontalLayout> buttons = ghnew HorizontalLayout();
            buttons->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
            buttons->Children = { playButton, stopButton };
            Children = { progressBar, buttons };
            playButton->Clicked.add([this](Control&, const MouseClickedEventArgs&) {
                sound->play();
                repaint();
                return true;
            });
            stopButton->Clicked.add([this](Control&, const MouseClickedEventArgs&) {
                sound->stop();
                return true;
            });
        }

        inline Audio::Sound* getSound() {
            return sound;
        }

        inline void setSound(Audio::Sound* sound) {
            this->sound = sound;
            playButton->Enabled = this->sound;
            stopButton->Enabled = this->sound;
        }

        __declspec(property(get = getSound, put = setSound)) Audio::Sound* Sound;

        virtual void onDraw(Canvas& canvas) override {
            __super::onDraw(canvas);
            if (sound && sound->isPlaying()) {
                progressBar->Progress = sound->Position/sound->Length;
                repaint();
            }
        }
    };
}