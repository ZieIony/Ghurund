#include "ghuipch.h"
#include "Clip.h"

#include "ui/Canvas.h"
#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    const Ghurund::Type& Clip::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Clip>();
        static const Ghurund::Type& TYPE = Ghurund::TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Clip))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

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

    Status Clip::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(shapeAttr->Value());
        return Status::OK;
    }
}
