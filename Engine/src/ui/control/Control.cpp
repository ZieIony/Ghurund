#include "ControlParent.h"

#include "core/logging/Logger.h"
#include "input/Mouse.h"
#include "ui/LayoutLoader.h"
#include "ui/style/Theme.h"

#include <regex>

namespace Ghurund::UI {

    const Ghurund::Type& Control::GET_TYPE() {
        static auto PROPERTY_NAME = TypedProperty<Control, const AString*>(GH_STRINGIFY(AString*), GH_STRINGIFY(Name), [](Control& control, const AString*& value) {
            value = control.Name;
        }, [](Control& control, const AString* const& value) {
            control.Name = value;
        });

        static auto PROPERTY_VISIBLE = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Visible), [](Control& control, bool& value) {
            value = control.Visible;
        }, [](Control& control, const bool& value) {
            control.Visible = value;
        });

        static auto PROPERTY_ENABLED = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Enabled), [](Control& control, bool& value) {
            value = control.Enabled;
        }, [](Control& control, const bool& value) {
            control.Enabled = value;
        });

        static auto PROPERTY_FOCUSABLE = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Focusable), [](Control& control, bool& value) {
            value = control.Focusable;
        }, [](Control& control, const bool& value) {
            control.Focusable = value;
        });

        static auto PROPERTY_FOCUSED = TypedProperty<Control, bool>("bool", GH_STRINGIFY(Focused), [](Control& control, bool& value) {value = control.isFocused(); });

        static auto PROPERTY_POSITION = TypedProperty<Control, const FloatPoint>("const FloatPoint&", GH_STRINGIFY(Position), [](Control& control, FloatPoint& value) {
            value = control.Position;
        }, [](Control& control, const FloatPoint& value) {
            control.Position = value;
        });

        static auto PROPERTY_ROTATION = TypedProperty<Control, float>("float", GH_STRINGIFY(Rotation), [](Control& control, float& value) {
            value = control.Rotation;
        }, [](Control& control, const float& value) {
            control.Rotation = value;
        });

        static auto PROPERTY_SCALE = TypedProperty<Control, const FloatPoint>("const FloatPoint&", GH_STRINGIFY(Scale), [](Control& control, FloatPoint& value) {
            value = control.Scale;
        }, [](Control& control, const FloatPoint& value) {
            control.Scale = value;
        });

        static auto PROPERTY_MINSIZE = TypedProperty<Control, FloatSize>(GH_STRINGIFY(FloatSize&), GH_STRINGIFY(MinSize), [](Control& control, FloatSize& value) {
            value = control.MinSize;
        }, [](Control& control, const FloatSize& value) {
            control.MinSize = value;
        });

        static auto PROPERTY_SIZE = TypedProperty<Control, const FloatSize>(GH_STRINGIFY(const FloatSize&), GH_STRINGIFY(Size), [](Control& control, FloatSize& value) {
            value = control.Size;
        });

        static auto PROPERTY_PREFERREDSIZE = TypedProperty<Control, Ghurund::UI::PreferredSize>(GH_STRINGIFY(PreferredSize&), GH_STRINGIFY(PreferredSize), [](Control& control, Ghurund::UI::PreferredSize& value) {
            value = control.PreferredSize;
        });

        static auto PROPERTY_MEASUREDSIZE = TypedProperty<Control, const FloatSize>(GH_STRINGIFY(const FloatSize&), GH_STRINGIFY(MeasuredSize), [](Control& control, FloatSize& value) {
            value = control.MeasuredSize;
        });

        static Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Control))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::TYPE)
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

    /*
    * measured size doesn't care about PreferredSize::FILL
    */
    void Control::onMeasure(float parentWidth, float parentHeight) {
        measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
        measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
    }

    bool Control::onMouseButtonEvent(const Ghurund::Input::MouseButtonEventArgs& event) {
        if (focusable && event.Action == Ghurund::Input::MouseAction::DOWN && !Focused)
            requestFocus();
        return false;
    }

    bool Control::isEnabled() const {
        return enabled && (!parent || parent->Enabled);
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
        if (!Focused && Focusable && parent) {
            parent->setFocus(this);
            onStateChanged();
            return true;
        }
        return false;
    }

    bool Control::focusPrevious() {
        if (!Focused && Focusable && parent) {
            parent->setFocus(this);
            onStateChanged();
            return true;
        }
        return false;
    }

    bool Control::focusUp() {
        if (!Focused && Focusable && parent) {
            parent->setFocus(this);
            onStateChanged();
            return true;
        }
        return false;
    }

    bool Control::focusDown() {
        if (!Focused && Focusable && parent) {
            parent->setFocus(this);
            onStateChanged();
            return true;
        }
        return false;
    }

    bool Control::focusLeft() {
        if (!Focused && Focusable && parent) {
            parent->setFocus(this);
            onStateChanged();
            return true;
        }
        return false;
    }

    bool Control::focusRight() {
        if (!Focused && Focusable && parent) {
            parent->setFocus(this);
            onStateChanged();
            return true;
        }
        return false;
    }

    void Control::setTheme(Ghurund::UI::Theme* theme) {
        if (localTheme != theme) {
            localTheme = theme;
            dispatchThemeChanged();
        }
    }

    Theme* Control::getTheme() {
        if (localTheme)
            return localTheme;
        if (parent)
            return parent->Theme;
        return nullptr;
    }

    void Control::dispatchStateChanged() {
        onStateChanged();
    }

    void Control::dispatchThemeChanged() {
        onThemeChanged();
        onStateChanged();
    }

    void Control::dispatchContextChanged() {
        if (parent)
            context = parent->Context;
        contextChanged();
    }

    void Control::repaint() {
        if (parent)
            parent->repaint();
    }

    void Control::invalidate() {
        needsLayout = true;
        if (parent)
            parent->invalidate();
    }

    void Control::layout(float x, float y, float width, float height) {
        if (position.x != x || position.y != y) {
            position.x = x;
            position.y = y;
            transformationInvalid = true;
        }
        if (needsLayout || size.width != width || size.height != height) {
            transformationInvalid = true;
#ifdef _DEBUG
            if (width < minSize.width || height < minSize.height)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is smaller than minSize\n", Type.Name, Name ? *Name : String("[unnamed]"));
            if (width == 0 || height == 0)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is [0, 0]\n", Type.Name, Name ? *Name : String("[unnamed]"));
#endif
            size.width = width;
            size.height = height;
            needsLayout = false;
            onLayout(x, y, size.width, size.height);
            onSizeChanged();
        }
    }

    void Control::draw(Canvas& canvas) {
        if (size.width == 0 || size.height == 0)
            return;
#ifdef _DEBUG
        if (!Theme) {
            Logger::log(LogType::WARNING, _T("cannot draw Control ({}: {}) because its theme is null\n"), Type.Name, Name ? *Name : String("[unnamed]"));
            return;
        }
#endif
        if (transformationInvalid)
            rebuildTransformation();
        canvas.save();
        canvas.transform(transformation);
        onDraw(canvas);
        canvas.restore();
    }

    FloatPoint Control::getPositionInWindow() {
        D2D1::Matrix3x2F matrix = D2D1::Matrix3x2F::Identity();
        Control* control = this;
        while (control) {
            matrix = matrix * control->Transformation;
            control = control->Parent;
        }
        D2D1_POINT_2F p = { 0,0 };
        matrix.TransformPoint(p);
        return FloatPoint{ p.x, p.y };
    }

    FloatPoint Control::getPositionOnScreen() {
        auto pos = PositionInWindow;
        if (!context)
            return pos;
        Ghurund::Window& window = context->Window;
        POINT p = { (LONG)pos.x, (LONG)pos.y };
        ClientToScreen(window.Handle, &p);
        return FloatPoint{ (float)p.x, (float)p.y };
    }

    Status Control::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        auto nameAttr = xml.FindAttribute("name");
        if (nameAttr)
            Name = nameAttr->Value();
        auto enabledAttr = xml.FindAttribute("enabled");
        if (enabledAttr)
            Enabled = enabledAttr->BoolValue();
        auto preferredSizeAttr = xml.FindAttribute("preferredSize");
        if (preferredSizeAttr) {
            AString size = preferredSizeAttr->Value();
            size_t comma = size.find(",");
            if (comma != size.Size) {
                AString width = size.substring(0, comma);
                if (width == "wrap") {
                    PreferredSize.width = PreferredSize::Width::WRAP;
                } else if (width == "fill") {
                    PreferredSize.width = PreferredSize::Width::FILL;
                } else {
                    PreferredSize.width = (float)atof(width.getData());
                }
                AString height = size.substring(comma + 1).trim();
                if (height == "wrap") {
                    PreferredSize.height = PreferredSize::Height::WRAP;
                } else if (height == "fill") {
                    PreferredSize.height = PreferredSize::Height::FILL;
                } else {
                    PreferredSize.height = (float)atof(height.getData());
                }
            }
        }
        auto minSizeAttr = xml.FindAttribute("minSize");
        if (minSizeAttr) {
            std::string str = minSizeAttr->Value();
            std::regex regex("(-?\\d+(?:\\.\\d+)?), *(-?\\d+(?:\\.\\d+)?)");
            std::smatch m;
            if (std::regex_match(str, m, regex) && m[2].matched) {
                minSize.width = (float)atof(m[1].str().c_str());
                minSize.height = (float)atof(m[2].str().c_str());
            }
        }
        auto styleAttr = xml.FindAttribute("style");
        if (styleAttr) {
            WString s = toWideChar(AString(styleAttr->Value()));
            uint32_t value = 0;
            const wchar_t* themeProtocol = L"theme://style/";
            if (s.startsWith(themeProtocol)) {
                WString styleKey = s.substring(lengthOf(themeProtocol));
                if (loader.Theme.Styles.contains(styleKey)) {
                    Style = loader.Theme.Styles[styleKey];
                } else {
                    Logger::log(LogType::WARNING, _T("missing style key {}\n"), styleKey);
                }
            }
        }
        return Status::OK;
    }

#ifdef _DEBUG
    String Control::logTree() {
        return fmt::format(_T("{}: {}, ref: {}\n"), Type.Name, Name ? *Name : String(_T("[unnamed]")), ReferenceCount).c_str();
    }
#endif

}
