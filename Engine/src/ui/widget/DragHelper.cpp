#include "DragHelper.h"

namespace Ghurund::UI {
    DragHelper::DragHelper(Control& handle, Control& content):onDragged(content) {
        handle.OnMouseButton.add([this, &content](Ghurund::Input::EventConsumer& sender, const Ghurund::Input::MouseButtonEventArgs& args) {
            if (args.Action == Ghurund::Input::MouseAction::DOWN && args.Button == Ghurund::Input::MouseButton::LEFT) {
                pressControlPos = content.Position;
                pressMousePos = args.Position;
                pressed = true;
            } else if (args.Action == Ghurund::Input::MouseAction::UP && args.Button == Ghurund::Input::MouseButton::LEFT) {
                pressed = false;
            }
            return true;
        });
        handle.OnMouseMotion.add([this, &content](Ghurund::Input::EventConsumer& sender, const Ghurund::Input::MouseMotionEventArgs& args) {
            Control* parent = content.Parent;
            if (pressed && parent) {
                auto prevControlPos = content.Position;
                content.Position = {
                    std::max(0.0f,std::min(content.Position.x + args.Delta.x, parent->Size.width - content.Size.width)),
                    std::max(0.0f,std::min(content.Position.y + args.Delta.y, parent->Size.height - content.Size.height))
                };
                if (prevControlPos.x != content.Position.x || prevControlPos.y != content.Position.y)
                    onDragged();
                return true;
            }
            return false;
        });
    }
}
