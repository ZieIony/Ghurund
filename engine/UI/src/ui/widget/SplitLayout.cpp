#include "ghuipch.h"
#include "SplitLayout.h"

#include "core/window/Cursor.h"

namespace Ghurund::UI {
    void Splitter::setOrientation(Ghurund::UI::Orientation orientation) {
        this->orientation = orientation;
        if (orientation == Orientation::HORIZONTAL) {
            //ContentSize.width = ContentSize::Width(std::max(ContentSize.width.Value, ContentSize.height.Value));
            //ContentSize.height = ContentSize::Height::FILL;
        } else {
            //ContentSize.height = ContentSize::Height(std::max(ContentSize.width.Value, ContentSize.height.Value));
            //ContentSize.width = ContentSize::Width::FILL;
        }
    }

    SplitLayout::SplitLayout(Ghurund::UI::Orientation orientation) {
        splitter.set(ghnew Splitter(orientation));
        //splitter->ContentSize.width = 4;
        //container1.set(ghnew ControlContainer());
        //container2.set(ghnew ControlContainer());
        LockedChild = LockedChild::NONE;
        //ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };

        //layout.set(ghnew LinearLayout());
        //layout->Children = { container1.get(), splitter.get(), container2.get() };
        //Child = layout.get();

        Orientation = orientation;
    }

    void SplitLayout::setOrientation(Ghurund::UI::Orientation orientation) {
        /*if (this->orientation == orientation)
            return;
        this->orientation = orientation;
        splitter->Orientation = orientation;
        layout->Orientation = orientation;
        splitter->mouseButtonEvent.clear();
        splitter->mouseMotionEvent.clear();
        if (orientation == Orientation::HORIZONTAL) {
            splitter->mouseButtonEvent += [this](EventConsumer& sender, const MouseButtonEventArgs& args) {
                if (args.Action == MouseAction::DOWN && args.Button == MouseButton::LEFT)
                    pressMousePos = args.Position;
                return true;
            };
            splitter->mouseMotionEvent += [this](EventConsumer& sender, const MouseMotionEventArgs& args) {
                if (splitter->Pressed[MouseButton::LEFT] || splitter->Hovered)
                    Cursor::SIZEWE.set();
                if (splitter->Pressed[MouseButton::LEFT]) {
                    if (lockedChild == LockedChild::NONE)
                        lockedChild = LockedChild::CHILD_1;
                    if (lockedChild == LockedChild::CHILD_1) {
                        //container1->ContentSize.width = container1->Size.Width + args.Position.x - pressMousePos.x;
                    } else {
                        //container2->ContentSize.width = container2->Size.Width - (args.Position.x - pressMousePos.x);
                    }
                    layout->requestLayout();
                }
                return true;
            };
        } else {
            splitter->mouseButtonEvent += [this](EventConsumer& sender, const MouseButtonEventArgs& args) {
                if (args.Action == MouseAction::DOWN && args.Button == MouseButton::LEFT)
                    pressMousePos = args.Position;
                return true;
            };
            splitter->mouseMotionEvent += [this](EventConsumer& sender, const MouseMotionEventArgs& args) {
                if (splitter->Pressed[MouseButton::LEFT] || splitter->Hovered)
                    Cursor::SIZENS.set();
                if (splitter->Pressed[MouseButton::LEFT]) {
                    if (lockedChild == LockedChild::NONE)
                        lockedChild = LockedChild::CHILD_1;
                    if (lockedChild == LockedChild::CHILD_1) {
                        //container1->ContentSize.height = container1->Size.Height + args.Position.y - pressMousePos.y;
                    } else {
                        //container2->ContentSize.height = container2->Size.Height - (args.Position.y - pressMousePos.y);
                    }
                    layout->requestLayout();
                }
                return true;
            };
        }*/
    }

    void SplitLayout::setChild1(Control* control) {
        container1->Child = control;
        /*if (control) {
            if (orientation == Orientation::HORIZONTAL) {
                if (control->ContentSize.width != ContentSize::Width::FILL) {
                    container1->ContentSize.width = control->ContentSize.width;
                    LockedChild = LockedChild::CHILD_1;
                }
            } else {
                if (control->ContentSize.height != ContentSize::Height::FILL) {
                    container1->ContentSize.height = control->ContentSize.height;
                    LockedChild = LockedChild::CHILD_1;
                }
            }
            control->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
        }*/
    }

    void SplitLayout::setChild2(Control* control) {
        container2->Child = control;
        /*if (control) {
            if (orientation == Orientation::HORIZONTAL) {
                if (control->ContentSize.width != ContentSize::Width::FILL) {
                    container2->ContentSize.width = control->ContentSize.width;
                    LockedChild = LockedChild::CHILD_2;
                }
            } else {
                if (control->ContentSize.height != ContentSize::Height::FILL) {
                    container2->ContentSize.height = control->ContentSize.height;
                    LockedChild = LockedChild::CHILD_2;
                }
            }
            control->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
        }*/
    }

    void SplitLayout::setLockedChild(Ghurund::UI::LockedChild child) {
        this->lockedChild = child;
        /*if (lockedChild == LockedChild::NONE) {
            container1->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
            container2->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
        } else if (lockedChild == LockedChild::CHILD_1) {
            if (orientation == Orientation::HORIZONTAL) {
                container1->ContentSize = {
                    container1->Size.Width > 0 ? (ContentSize::Width)container1->Size.Width : container1->ContentSize.width,
                    ContentSize::Height::FILL
                };
            } else {
                // TODO
                /*container1->ContentSize = {
                    ContentSize::Width::FILL,
                    container1->Size.height ? (ContentSize::Width)container1->Size.height : container1->ContentSize.height
                };* /
            }
            container2->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
        } else if (lockedChild == LockedChild::CHILD_2) {
            container1->ContentSize = { ContentSize::Width::FILL, ContentSize::Height::FILL };
            if (orientation == Orientation::HORIZONTAL) {
                container2->ContentSize = {
                    container2->Size.Width ? (ContentSize::Width)container2->Size.Width : container2->ContentSize.width,
                    ContentSize::Height::FILL
                };
            } else {
                // TODO
                /*container2->ContentSize = {
                    ContentSize::Width::FILL,
                    container2->Size.height ? (ContentSize::Width)container2->Size.height : container2->ContentSize.height
                };* /
            }
        }*/
    }
}