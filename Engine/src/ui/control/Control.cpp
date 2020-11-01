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

    void Control::requestFocus() {
        if (Focused || !focusable || !enabled)
            return;
        if (parent) {
            parent->setFocus(this);
            onStateChanged();
        }
    }

    void Control::clearFocus() {
        // TODO: this method requires to be called from a parent
        Control* focus = Focus;
        if (!focus)
            return;
        if (focus->Parent) {
            focus->Parent->clearChildFocus(this);
            focus->onStateChanged();
        }
    }

    bool Control::isFocused() const {
        // TODO: what about parent focus?
        return parent && parent->Focus == this;//&& parent->Focused;
    }

    bool Control::focusNext() {
        if (!Focused && focusable && parent) {
            parent->setFocus(this);
            return true;
        }
        return false;
    }

    bool Control::focusPrevious() {
        if (!Focused && focusable && parent) {
            parent->setFocus(this);
            return true;
        }
        return false;
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
            onSizeChanged();
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
        //ClientToScreen(Window->Handle, &p);
        return XMFLOAT2((float)p.x, (float)p.y);
    }

    const Ghurund::Type& Control::TYPE() {
        static auto& PROPERTY_NAME = TypedProperty<Control, const ASCIIString*>(GH_STRINGIFY(ASCIIString*), GH_STRINGIFY(Name), [](Control& control, const ASCIIString*& value) {
            value = control.Name;
        }, [](Control& control, const ASCIIString* const& value) {
            control.Name = value;
        });

        static auto& PROPERTY_VISIBLE = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Visible), [](Control& control, bool& value) {
            value = control.Visible;
        }, [](Control& control, const bool& value) {
            control.Visible = value;
        });

        static auto& PROPERTY_ENABLED = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Enabled), [](Control& control, bool& value) {
            value = control.Enabled;
        }, [](Control& control, const bool& value) {
            control.Enabled = value;
        });

        static auto& PROPERTY_FOCUSABLE = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Focusable), [](Control& control, bool& value) {
            value = control.Focusable;
        }, [](Control& control, const bool& value) {
            control.Focusable = value;
        });

        static auto PROPERTY_FOCUSED = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Focused), [](Control& control, bool& value) {value = control.isFocused(); });

        static auto& PROPERTY_POSITION = TypedProperty<Control, const XMFLOAT2>("const XMFLOAT2&", GH_STRINGIFY(Position), [](Control& control, XMFLOAT2& value) {
            value = control.Position;
        }, [](Control& control, const XMFLOAT2& value) {
            control.Position = value;
        });

        static auto& PROPERTY_ROTATION = TypedProperty<Control, float>("float", GH_STRINGIFY(Rotation), [](Control& control, float& value) {
            value = control.Rotation;
        }, [](Control& control, const float& value) {
            control.Rotation = value;
        });

        static auto& PROPERTY_SCALE = TypedProperty<Control, const XMFLOAT2>("const XMFLOAT2&", GH_STRINGIFY(Scale), [](Control& control, XMFLOAT2& value) {
            value = control.Scale;
        }, [](Control& control, const XMFLOAT2& value) {
            control.Scale = value;
        });

        static auto& PROPERTY_MINSIZE = TypedProperty<Control, FloatSize>(GH_STRINGIFY(FloatSize&), GH_STRINGIFY(MinSize), [](Control& control, FloatSize& value) {
            value = control.MinSize;
        }, [](Control& control, const FloatSize& value) {
            control.MinSize = value;
        });

        static auto& PROPERTY_SIZE = TypedProperty<Control, const FloatSize>(GH_STRINGIFY(const FloatSize&), GH_STRINGIFY(Size), [](Control& control, FloatSize& value) {
            value = control.Size;
        });

        static auto& PROPERTY_PREFERREDSIZE = TypedProperty<Control, Ghurund::UI::PreferredSize>(GH_STRINGIFY(PreferredSize&), GH_STRINGIFY(PreferredSize), [](Control& control, Ghurund::UI::PreferredSize& value) {
            value = control.PreferredSize;
        });

        static auto& PROPERTY_MEASUREDSIZE = TypedProperty<Control, const FloatSize>(GH_STRINGIFY(const FloatSize&), GH_STRINGIFY(MeasuredSize), [](Control& control, FloatSize& value) {
            value = control.MeasuredSize;
        });

        static Ghurund::Type TYPE = TypeBuilder<Control>(NAMESPACE_NAME, GH_STRINGIFY(Control))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(Pointer::TYPE)
            .withProperty(PROPERTY_NAME)
            .withProperty(PROPERTY_ENABLED)
            .withProperty(PROPERTY_FOCUSABLE)
            .withProperty(PROPERTY_FOCUSED)
            .withProperty(PROPERTY_VISIBLE)
            .withProperty(PROPERTY_POSITION)
            .withProperty(PROPERTY_ROTATION)
            .withProperty(PROPERTY_SCALE)
            .withProperty(PROPERTY_MINSIZE)
            .withProperty(PROPERTY_SIZE)
            .withProperty(PROPERTY_PREFERREDSIZE)
            .withProperty(PROPERTY_MEASUREDSIZE);

        return TYPE;
    }
}