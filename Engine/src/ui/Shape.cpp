#include "Shape.h"

namespace Ghurund::UI {
    void Rect::setBounds(const D2D_RECT_F& bounds) {
        path.Reset();
        graphics2d->Factory->CreateRectangleGeometry(bounds, (ID2D1RectangleGeometry**)path.GetAddressOf());

        __super::setBounds(bounds);
    }

    void RoundRect::setBounds(const D2D_RECT_F& bounds) {
        path.Reset();
        auto roundRect = D2D1::RoundedRect(bounds, cornerRadius, cornerRadius);
        graphics2d->Factory->CreateRoundedRectangleGeometry(roundRect, (ID2D1RoundedRectangleGeometry**)path.GetAddressOf());

        __super::setBounds(bounds);
    }

}
