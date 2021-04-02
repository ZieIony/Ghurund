#pragma once

#include "ui/widget/MenuBar.h"

class MainMenu:public Ghurund::UI::MenuBar {
public:
    MainMenu():MenuBar(makeTheme()){}

    Theme makeTheme()
};