#pragma once

#include "audio/Sound.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/ProgressBar.h"
#include "ui/widget/button/ImageButton.h"

namespace Ghurund::Editor {
    using namespace Ghurund::UI;

    class MusicPlayer:public VerticalLayout {
    private:
        ScopedPointer<ProgressBar> progressBar;
        ScopedPointer<ImageButton> playButton;
        ScopedPointer<ImageButton> stopButton;
        ScopedPointer<Audio::Sound> sound;

    public:
        MusicPlayer(Theme& theme) {
            PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
            progressBar = ghnew ProgressBar(*theme.progressBarStyle);
//            auto playIcon = makeScoped<BitmapImage>("icons/play 18.png");
            playButton = ghnew ImageButton(theme);
         //   playButton->Image = playIcon;
       //     auto stopIcon = makeScoped<BitmapImage>("icons/stop 18.png");
            stopButton = ghnew ImageButton(theme);
        //    stopButton->Image = stopIcon;
            ScopedPointer<HorizontalLayout> buttons = ghnew HorizontalLayout();
            buttons->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };
            buttons->Children = { playButton, stopButton };
            Children = { progressBar, buttons };
            playButton->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
                sound->play();
                repaint();
                return true;
            });
            stopButton->OnClicked.add([this](Control&, const MouseClickedEventArgs&) {
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