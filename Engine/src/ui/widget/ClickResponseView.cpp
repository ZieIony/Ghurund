#include "ghpch.h"
#include "ClickResponseView.h"

#include "ui/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Type& ClickResponseView::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ClickResponseView>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ClickResponseView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ClickResponseView::onUpdate(const uint64_t time) {
        if (Pressed)
            startTime = time;
        uint32_t dt = (uint32_t)(time - startTime);
        float percent = 1 - std::min(dt, length) / (float)length;
        finishedAnimating = percent == 0;
        color.A = percent;
    }

    void ClickResponseView::onDraw(Canvas& canvas) {
        canvas.fillRect(0, 0, Size.width, Size.height, color);
        if (!finishedAnimating)
            repaint();
    }
    
    Status ClickResponseView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = loader.loadColor(colorAttr->Value());
        return Status::OK;
    }
    
    void ClickResponseViewOnBackgroundStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        ((ClickResponseView&)control).Color = theme->Colors[Theme::COLOR_HIGHLIGHT_ONBACKGROUND];
    }
    
    void ClickResponseViewOnAccentStyle::onStateChanged(Control& control) const {
        Theme* theme = control.Theme;
        if (!theme)
            return;
        ((ClickResponseView&)control).Color = theme->Colors[Theme::COLOR_HIGHLIGHT_ONACCENT];
    }
}
