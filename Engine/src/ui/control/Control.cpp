#include "ControlParent.h"

namespace Ghurund::UI {
    void Control::onMeasure(float parentWidth, float parentHeight) {
        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = minSize.width;
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = minSize.height;
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
        }
    }

    void Control::onStateChanged() {
        if (parent)
            parent->onStateChanged();
    }

    Window* Control::getWindow() const {
        if (parent)
            return parent->Window;
        return nullptr;
    }

    void Control::repaint() {
        invalidateCache();
        if (parent)
            parent->repaint();
    }

    void Control::invalidate() {
        needsLayout = true;
        if (parent)
            parent->invalidate();
    }

    void Control::requestFocus() {
        focused = true;
        onStateChanged();
        if (parent)
            parent->setFocus(this);
    }

    void Control::layout(float x, float y, float width, float height) {
        position.x = x;
        position.y = y;
        transformationInvalid = true;
        if (needsLayout || size.width != width || size.height != height) {
#ifdef _DEBUG
            if (width < minSize.width || height < minSize.height)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is smaller than minSize\n", Type.Name, Name ? *Name : S("[unnamed]"));
            if (width == 0 || height == 0)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is 0\n", Type.Name, Name ? *Name : S("[unnamed]"));
            size.width = std::max(width, minSize.width);
            size.height = std::max(height, minSize.height);
#else
            size.width = width;
            size.height = height;
#endif
            needsLayout = false;
            onLayout(x, y, size.width, size.height);
        }
    }

    void Control::draw(Canvas& canvas) {
        if (transformationInvalid)
            rebuildTransformation();
        canvas.save();
        canvas.transform(*transformation);

        if (cacheEnabled) {
            if (!cache) {
                Canvas* c = canvas.beginCache((unsigned int)size.width, (unsigned int)size.height);
                onDraw(*c);
                cache = c->endCache();
                delete c;
            }
            cache->draw(canvas);
        } else {
            onDraw(canvas);
        }

        canvas.restore();
    }

    XMFLOAT2 Control::getPositionInWindow() {
        Gdiplus::Matrix matrix;
        Control* control = this;
        while (control) {
            matrix.Multiply(&control->Transformation);
            control = control->Parent;
        }
        Gdiplus::PointF p = { 0,0 };
        matrix.TransformPoints(&p);
        return XMFLOAT2(p.X, p.Y);
    }
    
    XMFLOAT2 Control::getPositionOnScreen() {
        auto pos = PositionInWindow;
        Ghurund::Window* window = Window;
        if (!window)
            return pos;
        POINT p = { (LONG)pos.x, (LONG)pos.y };
        ClientToScreen(Window->Handle, &p);
        return XMFLOAT2((float)p.x, (float)p.y);
    }
}