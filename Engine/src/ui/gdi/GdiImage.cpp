#include "GdiImage.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    void GdiImage::draw(Canvas& canvas) const {
        if (tint) {
            canvas.drawImage(*this, 0.0f, 0.0f, (float)size.width, (float)size.height, tint);
        } else {
            canvas.drawImage(*this, 0.0f, 0.0f, (float)size.width, (float)size.height);
        }
    }
}
