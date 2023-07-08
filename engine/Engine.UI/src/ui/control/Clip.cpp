#include "ghuipch.h"
#include "Clip.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Clip::GET_TYPE() {
        static auto PROPERTY_SHAPE = Property<Clip, std::unique_ptr<Ghurund::UI::Shape>&>("Shape", &setShape);

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
            canvas.clipRect(0, 0, Size.Width, Size.Height);
            __super::onDraw(canvas);
            canvas.restoreClipRect();
        }
    }
}
