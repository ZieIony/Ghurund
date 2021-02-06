#include "ClickResponseView.h"

#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    void ClickResponseView::onUpdate(const uint64_t time) {
        if (Pressed)
            startTime = time;
        uint32_t dt = (uint32_t)(time - startTime);
        float percent = 1 - std::min(dt, length) / (float)length;
        finishedAnimating = percent == 0;
        int32_t alpha = (int32_t)(percent * ((color >> 24) & 0xff));
        paint.Color = ((alpha & 0xff) << 24) | (color & 0xffffff);
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
}
