#include "ghuipch.h"
#include "Border.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Border::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Border>();
        static const Ghurund::Core::Type& TYPE = TypeBuilder<Border>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(Border))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Border::onDraw(ICanvas& canvas) {
        uint32_t color = Color.getValue(*this);
        if (!color || Thickness < 0.1f)
            return;
        if (shape) {
            canvas.drawShape(*shape, color, thickness);
        } else {
            canvas.drawRect(Position.x + Thickness / 2, Position.y + Thickness / 2, Size.width - Thickness, Size.height - Thickness, color, thickness);
        }
    }

    void Border::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(shapeAttr->Value());
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = *loader.loadColor(colorAttr->Value());
        auto thicknessAttr = xml.FindAttribute("thickness");
        if (thicknessAttr)
            Thickness = thicknessAttr->FloatValue();
    }
    
    void BorderOnBackgroundStyle::onStateChanged(Border& control) const {
        if (control.Enabled) {
            control.Color = ColorRef(Theme::COLOR_SECONDARY_ONBACKGROUND);
        } else {
            control.Color = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        }
    }
    
    void BorderAccentStyle::onStateChanged(Border& control) const {
        if (control.Enabled) {
            control.Color = ColorRef(Theme::COLOR_ACCENT);
        } else {
            control.Color = ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND);
        }
    }
}
