#include "ghuidxpch.h"
#include "Shape.h"

#include <d2d1.h>

namespace Ghurund::UI::Direct2D {
    Shape::~Shape() {
        if (path)
            path->Release();
    }

    void Rect::setBounds(const FloatRect& bounds) {
        if (path)
            path->Release();
        auto rect = D2D_RECT_F{ bounds.left, bounds.top, bounds.right, bounds.bottom };
        if (FAILED(d2dFactory.CreateRectangleGeometry(rect, (ID2D1RectangleGeometry**)&path)))
            throw CallFailedException();

        __super::setBounds(bounds);
    }

    void RoundRect::setBounds(const FloatRect& bounds) {
        if (path)
            path->Release();
        auto roundRect = D2D1::RoundedRect(D2D_RECT_F{ bounds.left, bounds.top, bounds.right, bounds.bottom }, cornerRadius, cornerRadius);
        if (FAILED(d2dFactory.CreateRoundedRectangleGeometry(roundRect, (ID2D1RoundedRectangleGeometry**)&path)))
            throw CallFailedException();

        __super::setBounds(bounds);
    }
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::Shape>() {
        static Type TYPE = Type(Ghurund::UI::Direct2D::NAMESPACE_NAME, "Shape", sizeof(Ghurund::UI::Direct2D::Shape));
        return TYPE;
    }
}
