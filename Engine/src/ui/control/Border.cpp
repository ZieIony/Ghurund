#include "Border.h"
#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    void Border::onDraw(Canvas& canvas) {
        if (!Color || Thickness < 0.1f)
            return;
        if (shape) {
            canvas.drawShape(*shape, paint);
        } else {
            canvas.drawRect(Position.x + Thickness / 2, Position.y + Thickness / 2, Size.width - Thickness, Size.height - Thickness, paint);
        }
    }

    Status Border::load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, context, xml);
        if (result != Status::OK)
            return result;
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(context, shapeAttr->Value());
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = loader.loadColor(colorAttr->Value());
        auto thicknessAttr = xml.FindAttribute("thickness");
        if (thicknessAttr)
            Thickness = thicknessAttr->FloatValue();
        return Status::OK;
    }
}
