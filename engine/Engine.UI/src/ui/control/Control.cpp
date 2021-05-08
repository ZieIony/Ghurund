#include "ghuipch.h"
#include "ControlParent.h"

#include "core/input/Mouse.h"
#include "ui/Cursor.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"

#include <regex>

namespace Ghurund::UI {

    Control::~Control() {
        delete name;
    }

    void Control::setName(const AString* name) {
        if (this->name)
            delete this->name;
        if (name)
            this->name = ghnew AString(*name);
    }

    void Control::setName(const AString& name) {
        if (this->name)
            delete this->name;
        this->name = ghnew AString(name);
    }

    /*
    * measured size doesn't care about PreferredSize::FILL
    */
    void Control::onMeasure(float parentWidth, float parentHeight) {
        measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
        measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
    }

    bool Control::onMouseButtonEvent(const Ghurund::MouseButtonEventArgs& event) {
        if (focusable && event.Action == Ghurund::MouseAction::DOWN && !Focused) {
            requestFocus();
            return true;
        }
        return false;
    }

    bool Control::isEnabled() const {
        return enabled && (!parent || parent->Enabled);
    }

    void Control::requestFocus() {
        if (Focused || !focusable || !enabled || !parent)
            return;

        Control* c = this;
        while (c->Parent) {
            if (c->Parent->Focus == nullptr) {
                c->Parent->Focus = c;
                c = c->Parent;
            } else if (c->Parent->Focus != c) {
                Control* f = c->Parent->Focus;
                c->Parent->Focus = c;
                while (f->Focus) {
                    Control* next = f->Focus;
                    f->Focus->Parent->Focus = nullptr;
                    f = next;
                }
                c = c->Parent;
                break;
            } else {
                return;
            }
        }
        c->dispatchStateChanged();
    }

    void Control::clearFocus() {
        if (!parent)
            return;
        Control* f = parent->Focus;
        if (!f)
            return;
        while (f) {
            Control* next = f->Focus;
            f->Parent->Focus = nullptr;
            f = next;
        }
        if (parent) {
            parent->Focus = nullptr;
            ControlParent* p = parent;
            while (p->Parent) {
                p->Focus = nullptr;
                p = p->Parent;
            }
            p->dispatchStateChanged();
        } else {
            dispatchStateChanged();
        }
    }

    bool Control::isFocused() const {
        return parent && parent->Focus == this && parent->Focused;
    }

    bool Control::focusNext() {
        if (!Focused && Focusable && parent) {
            requestFocus();
            return true;
        }
        return false;
    }

    bool Control::focusPrevious() {
        if (!Focused && Focusable && parent) {
            requestFocus();
            return true;
        }
        return false;
    }

    bool Control::focusUp() {
        if (!Focused && Focusable && parent) {
            requestFocus();
            return true;
        }
        return false;
    }

    bool Control::focusDown() {
        if (!Focused && Focusable && parent) {
            requestFocus();
            return true;
        }
        return false;
    }

    bool Control::focusLeft() {
        if (!Focused && Focusable && parent) {
            requestFocus();
            return true;
        }
        return false;
    }

    bool Control::focusRight() {
        if (!Focused && Focusable && parent) {
            requestFocus();
            return true;
        }
        return false;
    }

    void Control::setParent(ControlParent* parent) {
        bool contextChanged = parent && Context != parent->Context;
        bool themeChanged = parent && Theme != parent->Theme;
        this->parent = parent;
        if (contextChanged)
            dispatchContextChanged();
        if (themeChanged)
            dispatchThemeChanged();
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

    UIContext* Control::getContext() {
        if (parent)
            return parent->Context;
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
        }
        if (needsLayout || size.width != width || size.height != height) {
#ifdef _DEBUG
            /*const char* name = Name ? Name->Data : "[unnamed]";
            if (width < minSize.width || height < minSize.height)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is smaller than minSize\n", Type.Name, name);
            if (width == 0 || height == 0)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is [0, 0]\n", Type.Name, name);*/
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
        /*        if (!Theme) {
                    Logger::log(LogType::WARNING, _T("cannot draw Control ({}: {}) because its theme is null\n"), Type.Name, Name ? *Name : String("[unnamed]"));
                    return;
                }*/
#endif
        canvas.save();
        canvas.translate(position.x, position.y);
        onDraw(canvas);
        canvas.restore();
    }

    Control* Control::find(const AString& name) {
        if (this->name && this->name->operator==(name))
            return this;
        return nullptr;
    }

    Control* Control::find(const Ghurund::Type& type) {
        if (Type == type)
            return this;
        return nullptr;
    }

    FloatPoint Control::getPositionInWindow() {
        Control* control = this;
        while (control) {
            //matrix = matrix * control->Transformation;
            control = control->Parent;
        }
        //D2D1_POINT_2F p = { 0,0 };
        //matrix.TransformPoint(p);
        return FloatPoint{ 0, 0 };
    }

    FloatPoint Control::getPositionOnScreen() {
        auto pos = PositionInWindow;
        UIContext* context = Context;
        if (!context)
            return pos;
        Ghurund::Window& window = context->Window;
        POINT p = { (LONG)pos.x, (LONG)pos.y };
        //ClientToScreen(window.Handle, &p);
        return FloatPoint{ (float)p.x, (float)p.y };
    }

    bool Control::dispatchMouseMotionEvent(const Ghurund::MouseMotionEventArgs& event) {
        bool result = __super::dispatchMouseMotionEvent(event);
        if (!result && cursor) {
            cursor->set();
            return true;
        }
        return result;
    }

    Status Control::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        auto nameAttr = xml.FindAttribute("name");
        if (nameAttr)
            Name = nameAttr->Value();
        auto enabledAttr = xml.FindAttribute("enabled");
        if (enabledAttr)
            Enabled = enabledAttr->BoolValue();
        auto visibleAttr = xml.FindAttribute("visible");
        if (visibleAttr)
            Visible = visibleAttr->BoolValue();
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
            AString s = styleAttr->Value();
            s.replace('\\', '/');
            uint32_t value = 0;
            if (s.startsWith(LayoutLoader::THEME_STYLE)) {
                StyleKey styleKey = s.substring(lengthOf(LayoutLoader::THEME_STYLE));
                if (loader.Theme.Styles.containsKey(styleKey)) {
                    Style = loader.Theme.Styles[styleKey];
                } else {
                    Logger::log(LogType::WARNING, _T("invalid style key {}\n"), styleKey.str);
                }
            }
        } else if (loader.Theme.Styles.containsKey(StyleKey(Type.Name))) {
            Style = loader.Theme.Styles[StyleKey(Type.Name)];
        }

        return Status::OK;
    }

#ifdef _DEBUG
    void Control::validate() {
        _ASSERTE(ReferenceCount < 1000);
        _ASSERTE(!parent || parent->ReferenceCount < 1000);
    }
#endif
}
