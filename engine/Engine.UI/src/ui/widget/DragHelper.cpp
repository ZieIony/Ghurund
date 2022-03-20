#include "ghuipch.h"
#include "DragHelper.h"

namespace Ghurund::UI {
    DragHelper::DragHelper(Control& handle, Control& content):dragged(content) {
        handle.mouseButtonEvent += [this, &content](EventConsumer& sender, const MouseButtonEventArgs& args) {
            if (args.Action == MouseAction::DOWN && args.Button == MouseButton::LEFT) {
                pressControlPos = content.Position;
                pressMousePos = args.Position;
                pressed = true;
            } else if (args.Action == MouseAction::UP && args.Button == MouseButton::LEFT) {
                pressed = false;
            }
            return true;
        };
        handle.mouseMotionEvent += [this, &content](EventConsumer& sender, const MouseMotionEventArgs& args) {
            Control* parent = content.Parent;
            if (pressed && parent) {
                auto prevControlPos = content.Position;
                content.Position = {
                    std::max(0.0f,std::min(content.Position.x + args.Delta.x, parent->Size.Width - content.Size.Width)),
                    std::max(0.0f,std::min(content.Position.y + args.Delta.y, parent->Size.Height - content.Size.Height))
                };
                if (prevControlPos.x != content.Position.x || prevControlPos.y != content.Position.y)
                    dragged();
                return true;
            }
            return false;
        };
    }
}
