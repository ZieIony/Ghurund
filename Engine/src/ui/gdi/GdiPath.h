#pragma once

#include "Gdi.h"

namespace Ghurund::UI {
    class GdiPath {
    public:
        Gdiplus::GraphicsPath* path;

        GdiPath() {
            path = new Gdiplus::GraphicsPath();
        }

        ~GdiPath() {
            delete path;
        }

        void setRect(const Gdiplus::RectF& rect) {
            path->Reset();
            path->AddRectangle(rect);
        }

        void setRoundRect(const Gdiplus::RectF& rect, float radius) {
            path->Reset();
            path->AddLine(rect.X + radius, rect.Y, rect.X + rect.Width - (radius * 2), rect.Y);
            path->AddArc(rect.X + rect.Width - (radius * 2), rect.Y, radius * 2, radius * 2, 270, 90);
            path->AddLine(rect.X + rect.Width, rect.Y + radius, rect.X + rect.Width, rect.Y + rect.Height - (radius * 2));
            path->AddArc(rect.X + rect.Width - (radius * 2), rect.Y + rect.Height - (radius * 2), radius * 2, radius * 2, 0, 90);
            path->AddLine(rect.X + rect.Width - (radius * 2), rect.Y + rect.Height, rect.X + radius, rect.Y + rect.Height);
            path->AddArc(rect.X, rect.Y + rect.Height - (radius * 2), radius * 2, radius * 2, 90, 90);
            path->AddLine(rect.X, rect.Y + rect.Height - (radius * 2), rect.X, rect.Y + radius);
            path->AddArc(rect.X, rect.Y, radius * 2, radius * 2, 180, 90);
            path->CloseFigure();
        }
    };
}