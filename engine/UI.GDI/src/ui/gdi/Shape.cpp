#include "ghuigdipch.h"
#include "Shape.h"

namespace Ghurund::UI::GDI {
    Shape::~Shape() {
        delete path;
    }

    void Rect::setBounds(const FloatRect& bounds) {
        path->Reset();
        path->AddRectangle(Gdiplus::RectF{ bounds.left, bounds.top, bounds.Width, bounds.Height });

        __super::setBounds(bounds);
    }

    void RoundRect::setBounds(const FloatRect& bounds) {
        path->Reset();
        path->AddLine(bounds.left + cornerRadius, bounds.top, bounds.left + bounds.Width - (cornerRadius * 2), bounds.top);
        path->AddArc(bounds.left + bounds.Width - (cornerRadius * 2), bounds.top, cornerRadius * 2, cornerRadius * 2, 270, 90);
        path->AddLine(bounds.left + bounds.Width, bounds.top + cornerRadius, bounds.left + bounds.Width, bounds.top + bounds.Height - (cornerRadius * 2));
        path->AddArc(bounds.left + bounds.Width - (cornerRadius * 2), bounds.top + bounds.Height - (cornerRadius * 2), cornerRadius * 2, cornerRadius * 2, 0, 90);
        path->AddLine(bounds.left + bounds.Width - (cornerRadius * 2), bounds.top + bounds.Height, bounds.left + cornerRadius, bounds.top + bounds.Height);
        path->AddArc(bounds.left, bounds.top + bounds.Height - (cornerRadius * 2), cornerRadius * 2, cornerRadius * 2, 90, 90);
        path->AddLine(bounds.left, bounds.top + bounds.Height - (cornerRadius * 2), bounds.left, bounds.top + cornerRadius);
        path->AddArc(bounds.left, bounds.top, cornerRadius * 2, cornerRadius * 2, 180, 90);
        path->CloseFigure();;

        __super::setBounds(bounds);
    }
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::GDI::Shape>() {
        static Type TYPE = Type(Ghurund::UI::GDI::NAMESPACE_NAME, "Shape", sizeof(Ghurund::UI::GDI::Shape));
        return TYPE;
    }
}
