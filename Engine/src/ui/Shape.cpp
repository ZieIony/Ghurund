#include "Shape.h"
#include "Graphics2D.h"

namespace Ghurund::UI {
    Shape::~Shape() {
        if (path)
            path->Release();
    }
    
    void Rect::setBounds(const FloatRect& bounds) {
        graphics2d->Factory->CreateRectangleGeometry(D2D_RECT_F{ bounds.left, bounds.top, bounds.right, bounds.bottom }, (ID2D1RectangleGeometry**)&path);

        __super::setBounds(bounds);
    }

    void RoundRect::setBounds(const FloatRect& bounds) {
        auto roundRect = D2D1::RoundedRect(D2D_RECT_F{ bounds.left, bounds.top, bounds.right, bounds.bottom }, cornerRadius, cornerRadius);
        graphics2d->Factory->CreateRoundedRectangleGeometry(roundRect, (ID2D1RoundedRectangleGeometry**)&path);

        __super::setBounds(bounds);
    }
}
