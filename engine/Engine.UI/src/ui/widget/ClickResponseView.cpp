#include "ghuipch.h"
#include "ClickResponseView.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ClickResponseView::GET_TYPE() {
        static auto CONSTRUCTOR = Constructor<ClickResponseView>();
        //static auto CONSTRUCTOR_COLOR = Constructor<ClickResponseView, const Ghurund::UI::Color&>();
        //static auto PROPERTY_COLOR = Property<ClickResponseView, const Ghurund::UI::Color&>("Color", &getColor, &setColor);

        static const Ghurund::Core::Type TYPE = TypeBuilder<ClickResponseView>(Ghurund::UI::NAMESPACE_NAME, "ClickResponseView")
            //.withProperty(PROPERTY_COLOR)
            .withConstructor(CONSTRUCTOR)
            //.withConstructor(CONSTRUCTOR_COLOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ClickResponseView::onUpdate(const uint64_t time) {
        if (Pressed)
            startTime = time;
        uint32_t dt = (uint32_t)(time - startTime);
        float percent = 1 - std::min(dt, length) / (float)length;
        finishedAnimating = percent == 0;
        alpha = percent;
    }

    void ClickResponseView::onDraw(ICanvas& canvas) {
        Ghurund::UI::Color c = color->getValue(*this);
        c.A = alpha;
        canvas.fillRect(0, 0, Size.width, Size.height, c);
        if (!finishedAnimating)
            repaint();
    }
    
    void ClickResponseView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        auto colorAttr = xml.FindAttribute("color");
        if (colorAttr)
            Color = *loader.loadColor(colorAttr->Value());
    }
    
    void ClickResponseViewOnBackgroundStyle::onStateChanged(Control& control) const {
        ((ClickResponseView&)control).Color = ColorRef(Theme::COLOR_HIGHLIGHT_ONBACKGROUND);
    }
    
    void ClickResponseViewOnAccentStyle::onStateChanged(Control& control) const {
        ((ClickResponseView&)control).Color = ColorRef(Theme::COLOR_HIGHLIGHT_ONACCENT);
    }
}
