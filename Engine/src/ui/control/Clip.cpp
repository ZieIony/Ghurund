#include "Clip.h"
#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    void Clip::onDraw(Canvas& canvas) {
        if (shape) {
            canvas.clipShape(*shape);
            __super::onDraw(canvas);
            canvas.restoreClipShape();
        } else {
            canvas.clipRect(0, 0, Size.width, Size.height);
            __super::onDraw(canvas);
            canvas.restoreClipRect();
        }
    }

    Status Clip::load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, context, xml);
        if (result != Status::OK)
            return result;
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(context, shapeAttr->Value());
        return Status::OK;
    }
}
