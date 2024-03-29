#include "ghuipch.h"
#include "Clip.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Clip::GET_TYPE() {
        static auto PROPERTY_SHAPE = Property<Clip, Ghurund::UI::Shape*>("Shape", (Ghurund::UI::Shape * (Clip::*)()) & getShape, (void(Clip::*)(Ghurund::UI::Shape*)) & setShape);

        static const auto CONSTRUCTOR = Constructor<Clip>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Clip>("Ghurund::UI", "Clip")
            .withProperty(PROPERTY_SHAPE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Clip::onDraw(ICanvas& canvas) {
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

    void Clip::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(shapeAttr->Value());
    }
}
