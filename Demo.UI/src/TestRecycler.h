#pragma once

#include "TestRecyclerBinding.h"
#include "ui/widget/Widget.h"

namespace Demo {
    class TestRecycler:public Widget<TestRecyclerBinding> {
    protected:
        virtual void onLayoutChanged() override {
            if (!Layout)
                return;
            /*Layout->Clickable->StateChanged.add(stateHandler);
            Layout->Clickable->Clicked.add([this](Control&, const MouseClickedEventArgs& args) {
                return clicked(args);
            });*/
        }

    public:

    };
}