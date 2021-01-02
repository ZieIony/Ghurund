#include "DragHelper.h"

namespace Ghurund::UI {
    DragHelper::DragHelper(Control& handle, Control& content):onDragged(content) {
        handle.OnMouseButton.add([this, &content](Input::EventConsumer& sender, const Input::MouseButtonEventArgs& args) {
            if (args.Action == Input::MouseAction::DOWN && args.Button == Input::MouseButton::LEFT) {
                pressControlPos = content.Position;
                pressMousePos = args.Position;
                pressed = true;
            } else if (args.Action == Input::MouseAction::UP && args.Button == Input::MouseButton::LEFT) {
                pressed = false;
            }
            return true;
        });
        handle.OnMouseMotion.add([this, &content](Input::EventConsumer& sender, const Input::MouseMotionEventArgs& args) {
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
