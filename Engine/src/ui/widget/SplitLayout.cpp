#include "SplitLayout.h"

namespace Ghurund::UI {
    void Splitter::setOrientation(Ghurund::UI::Orientation orientation) {
        this->orientation = orientation;
        if (orientation == Orientation::HORIZONTAL) {
            PreferredSize.width = PreferredSize::Width(std::max((float)PreferredSize.width, (float)PreferredSize.height));
            PreferredSize.height = PreferredSize::Height::FILL;
        } else {
            PreferredSize.height = PreferredSize::Height(std::max((float)PreferredSize.width, (float)PreferredSize.height));
            PreferredSize.width = PreferredSize::Width::FILL;
        }
    }

    SplitLayout::SplitLayout(Ghurund::UI::Orientation orientation) {
        splitter = ghnew Splitter(orientation);
        splitter->PreferredSize.width = 4;
        container1 = ghnew ControlContainer();
        container2 = ghnew ControlContainer();
        LockedChild = LockedChild::NONE;
        PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };

        layout = ghnew LinearLayout();
        layout->Children = { container1, splitter, container2 };
        Child = layout;

        Orientation = orientation;
    }

    void SplitLayout::setOrientation(Ghurund::UI::Orientation orientation) {
        if (this->orientation == orientation)
            return;
        this->orientation = orientation;
        splitter->Orientation = orientation;
        layout->Orientation = orientation;
        splitter->OnMouseButton.clear();
        splitter->OnMouseMotion.clear();
        if (orientation == Orientation::HORIZONTAL) {
            splitter->OnMouseButton.add([this](EventConsumer& sender, const MouseButtonEventArgs& args) {
                if (args.Action == MouseAction::DOWN && args.Button == MouseButton::LEFT)
                    pressMousePos = args.Position;
                return true;
            });
            splitter->OnMouseMotion.add([this](EventConsumer& sender, const MouseMotionEventArgs& args) {
                if (splitter->Pressed[MouseButton::LEFT] || splitter->Hovered)
                    Cursor::SIZEWE.set();
                if (splitter->Pressed[MouseButton::LEFT]) {
                    if (lockedChild == LockedChild::NONE)
                        lockedChild = LockedChild::CHILD_1;
                    if (lockedChild == LockedChild::CHILD_1) {
                        container1->PreferredSize.width = container1->Size.width + args.Position.x - pressMousePos.x;
                    } else {
                        container2->PreferredSize.width = container2->Size.width - (args.Position.x - pressMousePos.x);
                    }
                    layout->invalidate();
                }
                return true;
            });
        } else {
            splitter->OnMouseButton.add([this](EventConsumer& sender, const MouseButtonEventArgs& args) {
                if (args.Action == MouseAction::DOWN && args.Button == MouseButton::LEFT)
                    pressMousePos = args.Position;
                return true;
            });
            splitter->OnMouseMotion.add([this](EventConsumer& sender, const MouseMotionEventArgs& args) {
                if (splitter->Pressed[MouseButton::LEFT] || splitter->Hovered)
                    Cursor::SIZENS.set();
                if (splitter->Pressed[MouseButton::LEFT]) {
                    if (lockedChild == LockedChild::NONE)
                        lockedChild = LockedChild::CHILD_1;
                    if (lockedChild == LockedChild::CHILD_1) {
                        container1->PreferredSize.height = container1->Size.height + args.Position.y - pressMousePos.y;
                    } else {
                        container2->PreferredSize.height = container2->Size.height - (args.Position.y - pressMousePos.y);
                    }
                    layout->invalidate();
                }
                return true;
            });
        }
    }

    void SplitLayout::setChild1(Control* control) {
        container1->Child = control;
        if (control) {
            if (orientation == Orientation::HORIZONTAL) {
                if (control->PreferredSize.width != PreferredSize::Width::FILL) {
                    container1->PreferredSize.width = control->PreferredSize.width;
                    LockedChild = LockedChild::CHILD_1;
                }
            } else {
                if (control->PreferredSize.height != PreferredSize::Height::FILL) {
                    container1->PreferredSize.height = control->PreferredSize.height;
                    LockedChild = LockedChild::CHILD_1;
                }
            }
            control->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }
    }

    void SplitLayout::setChild2(Control* control) {
        container2->Child = control;
        if (control) {
            if (orientation == Orientation::HORIZONTAL) {
                if (control->PreferredSize.width != PreferredSize::Width::FILL) {
                    container2->PreferredSize.width = control->PreferredSize.width;
                    LockedChild = LockedChild::CHILD_2;
                }
            } else {
                if (control->PreferredSize.height != PreferredSize::Height::FILL) {
                    container2->PreferredSize.height = control->PreferredSize.height;
                    LockedChild = LockedChild::CHILD_2;
                }
            }
            control->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }
    }

    void SplitLayout::setLockedChild(Ghurund::UI::LockedChild child) {
        this->lockedChild = child;
        if (lockedChild == LockedChild::NONE) {
            container1->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            container2->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        } else if (lockedChild == LockedChild::CHILD_1) {
            if (orientation == Orientation::HORIZONTAL) {
                container1->PreferredSize = {
                    container1->Size.width > 0 ? (PreferredSize::Width)container1->Size.width : container1->PreferredSize.width,
                    PreferredSize::Height::FILL
                };
            } else {
                container1->PreferredSize = {
                    PreferredSize::Width::FILL,
                    container1->Size.height ? (PreferredSize::Width)container1->Size.height : container1->PreferredSize.height
                };
            }
            container2->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        } else if (lockedChild == LockedChild::CHILD_2) {
            container1->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
            if (orientation == Orientation::HORIZONTAL) {
                container2->PreferredSize = {
                    container2->Size.width ? (PreferredSize::Width)container2->Size.width : container2->PreferredSize.width,
                    PreferredSize::Height::FILL
                };
            } else {
                container2->PreferredSize = {
                    PreferredSize::Width::FILL,
                    container2->Size.height ? (PreferredSize::Width)container2->Size.height : container2->PreferredSize.height
                };
            }
        }
    }
}