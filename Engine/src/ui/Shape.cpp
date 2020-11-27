#include "Shape.h"

namespace Ghurund::UI {
    void Rect::setBounds(const D2D_RECT_F& bounds) {
        ComPtr<ID2D1GeometrySink> sink;
        path.Reset();
        graphics2d->Factory->CreatePathGeometry(&path);
        path->Open(sink.GetAddressOf());
        sink->SetFillMode(D2D1_FILL_MODE_WINDING);
        sink->BeginFigure(D2D1::Point2F(bounds.left, bounds.top), D2D1_FIGURE_BEGIN_FILLED);
        sink->AddLine(D2D1::Point2F(bounds.right, bounds.top));
        sink->AddLine(D2D1::Point2F(bounds.right, bounds.bottom));
        sink->AddLine(D2D1::Point2F(bounds.left, bounds.bottom));
        sink->AddLine(D2D1::Point2F(bounds.left, bounds.top));
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
        sink->Close();

        __super::setBounds(bounds);
    }

    void RoundRect::setBounds(const D2D_RECT_F& bounds) {
        ComPtr<ID2D1GeometrySink> sink;
        path.Reset();
        graphics2d->Factory->CreatePathGeometry(&path);
        path->Open(sink.GetAddressOf());
        sink->SetFillMode(D2D1_FILL_MODE_WINDING);
        sink->BeginFigure(D2D1::Point2F(bounds.left, bounds.top), D2D1_FIGURE_BEGIN_FILLED);
        //sink->AddArc(D2D1::ArcSegment())
        sink->AddLine(D2D1::Point2F(bounds.right, bounds.top));
        sink->AddLine(D2D1::Point2F(bounds.right, bounds.bottom));
        sink->AddLine(D2D1::Point2F(bounds.left, bounds.bottom));
        sink->AddLine(D2D1::Point2F(bounds.left, bounds.top));
        sink->EndFigure(D2D1_FIGURE_END_CLOSED);
        sink->Close();

        __super::setBounds(bounds);
    }

}
