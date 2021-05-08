#include "ghuipch.h"
#include "Border.h"

#include "ui/layout/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Type& Border::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Border>();
        static const Ghurund::Type& TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Border))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Border::onDraw(Canvas& canvas) {
        if (!Color || Thickness < 0.1f)
            return;
        if (shape) {
            canvas.drawShape(*shape, color, thickness);
        } else {
            canvas.drawRect(Position.x + Thickness / 2, Position.y + Thickness / 2, Size.width - Thickness, Size.height - Thickness, color, thickness);
        }
    }

    Status Border::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto shapeAttr = xml.FindAttribute("shape");
        if (shapeAttr)
            Shape = loader.loadShape(shapeAttr->Value());
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = loader.loadColor(colorAttr->Value());
        auto thicknessAttr = xml.FindAttribute("thickness");
        if (thicknessAttr)
            Thickness = thicknessAttr->FloatValue();
        return Status::OK;
    }
    
    void BorderOnBackgroundStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        if (control.Enabled) {
            ((Border&)control).Color = theme->Colors[Theme::COLOR_SECONDARY_ONBACKGROUND];
        } else {
            ((Border&)control).Color = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        }
    }
    
    void BorderAccentStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        if (control.Enabled) {
            ((Border&)control).Color = theme->Colors[Theme::COLOR_ACCENT];
        } else {
            ((Border&)control).Color = theme->Colors[Theme::COLOR_DISABLED_ONBACKGROUND];
        }
    }
}
