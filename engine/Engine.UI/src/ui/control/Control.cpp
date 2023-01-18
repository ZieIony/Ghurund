#include "ghuipch.h"
#include "ControlParent.h"
#include "ControlGroup.h"

#include "core/input/Mouse.h"
#include "ui/Cursor.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/Canvas.h"
#include "core/reflection/TypeBuilder.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/Property.h"

#include <regex>

namespace Ghurund::UI {

    const Ghurund::Core::Type& Control::GET_TYPE() {
        static auto PROPERTY_NAME = Property<Control, const AString*>("Name", (AString * (Control::*)()) & getName, (void(Control::*)(const AString*)) & setName);
        static auto PROPERTY_VISIBLE = Property<Control, bool>("Visible", (bool(Control::*)()) & isVisible, (void(Control::*)(bool)) & setVisible);
        static auto PROPERTY_ENABLED = Property<Control, bool>("Enabled", (bool(Control::*)()) & isEnabled, (void(Control::*)(bool)) & setEnabled);
        static auto PROPERTY_FOCUSABLE = Property<Control, bool>("Focusable", (bool(Control::*)()) & isFocusable, (void(Control::*)(bool)) & setFocusable);
        static auto PROPERTY_FOCUS = Property<Control, Control*>("Focus", &getFocus);
        static auto PROPERTY_FOCUSED = Property<Control, bool>("Focused", (bool(Control::*)()) & isFocused);
        static auto PROPERTY_POSITION = Property<Control, const FloatPoint&>("Position", (FloatPoint & (Control::*)()) & getPosition, (void(Control::*)(const FloatPoint&)) & setPosition);
        static auto PROPERTY_ROTATION = Property<Control, float>("Rotation", (float(Control::*)()) & getRotation, (void(Control::*)(float)) & setRotation);
        static auto PROPERTY_SCALE = Property<Control, const FloatPoint&>("Scale", (FloatPoint & (Control::*)()) & getScale, (void(Control::*)(const FloatPoint&)) & setScale);
        static auto PROPERTY_TRANSFORMATION = Property<Control, const Matrix3x2&>("Transformation", (Matrix3x2 & (Control::*)()) & getTransformation);
        static auto PROPERTY_SIZE = Property<Control, FloatSize&>("Size", (FloatSize & (Control::*)()) & getSize);
        static auto PROPERTY_PREFERREDSIZE = Property<Control, const Ghurund::UI::PreferredSize&>("PreferredSize", (Ghurund::UI::PreferredSize & (Control::*)()) & getPreferredSize, (void(Control::*)(const Ghurund::UI::PreferredSize&)) & setPreferredSize);
        static auto PROPERTY_MEASUREDSIZE = Property<Control, FloatSize&>("MeasuredSize", (FloatSize & (Control::*)()) & getMeasuredSize);
        static auto PROPERTY_PARENT = Property<Control, ControlParent*>("Parent", (ControlParent * (Control::*)()) & getParent, (void(Control::*)(ControlParent*)) & setParent);
        static auto PROPERTY_CURSOR = Property<Control, const Ghurund::UI::Cursor*>("Cursor", (Ghurund::UI::Cursor * (Control::*)()) & getCursor, (void(Control::*)(const Ghurund::UI::Cursor*)) & setCursor);
        static auto PROPERTY_THEME = Property<Control, Ghurund::UI::Theme*>("Theme", (Ghurund::UI::Theme * (Control::*)()) & getTheme, (void(Control::*)(Ghurund::UI::Theme*)) & setTheme);
        static auto PROPERTY_CONTEXT = Property<Control, IUIContext*>("Context", (IUIContext * (Control::*)()) & getContext);
        static auto PROPERTY_STYLE = Property<Control, const Ghurund::UI::Style*>("Style", (Ghurund::UI::Style * (Control::*)()) & getStyle, (void(Control::*)(const Ghurund::UI::Style*)) & setStyle);
        static auto PROPERTY_POSITIONINWINDOW = Property<Control, FloatPoint>("PositionInWindow", (FloatPoint(Control::*)()) & getPositionInWindow);
        static auto PROPERTY_POSITIONONSCREEN = Property<Control, FloatPoint>("PositionOnScreen", (FloatPoint(Control::*)()) & getPositionOnScreen);

        static const Ghurund::Core::Type TYPE = TypeBuilder<Control>(Ghurund::UI::NAMESPACE_NAME, "Control")
            .withProperty(PROPERTY_NAME)
            .withProperty(PROPERTY_VISIBLE)
            .withProperty(PROPERTY_ENABLED)
            .withProperty(PROPERTY_FOCUSABLE)
            .withProperty(PROPERTY_FOCUS)
            .withProperty(PROPERTY_FOCUSED)
            .withProperty(PROPERTY_POSITION)
            .withProperty(PROPERTY_ROTATION)
            .withProperty(PROPERTY_SCALE)
            .withProperty(PROPERTY_TRANSFORMATION)
            .withProperty(PROPERTY_SIZE)
            .withProperty(PROPERTY_PREFERREDSIZE)
            .withProperty(PROPERTY_MEASUREDSIZE)
            .withProperty(PROPERTY_PARENT)
            .withProperty(PROPERTY_CURSOR)
            .withProperty(PROPERTY_THEME)
            .withProperty(PROPERTY_CONTEXT)
            .withProperty(PROPERTY_STYLE)
            .withProperty(PROPERTY_POSITIONINWINDOW)
            .withProperty(PROPERTY_POSITIONONSCREEN)
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

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

    float Control::resolveWidth(float contentSize, float parentWidth, float parentHeight) const {
        float width;
        switch (preferredSize.width.Type) {
        case PreferredSize::Type::PIXELS:
            width = preferredSize.width.Value;
            break;
        case PreferredSize::Type::FILL:
            width = parentWidth * preferredSize.width.Value;
            break;
        case PreferredSize::Type::WRAP:
            width = contentSize;
            break;
        case PreferredSize::Type::PERCENT:
            width = parentWidth * preferredSize.width.Value * 0.01f;
            break;
        case PreferredSize::Type::RATIO:
            return std::min(maxSize.height.resolve(parentHeight), std::max(preferredSize.height.Value, minSize.height.resolve(parentHeight))) * preferredSize.width.Value;
        }
        return std::min(maxSize.width.resolve(parentWidth), std::max(width, minSize.width.resolve(parentWidth)));
    }

    float Control::resolveHeight(float contentSize, float parentWidth, float parentHeight) const {
        float height;
        switch (preferredSize.height.Type) {
        case PreferredSize::Type::PIXELS:
            height = preferredSize.height.Value;
            break;
        case PreferredSize::Type::FILL:
            height = parentHeight * preferredSize.height.Value;
            break;
        case PreferredSize::Type::WRAP:
            height = contentSize;
            break;
        case PreferredSize::Type::PERCENT:
            height = parentHeight * preferredSize.height.Value * 0.01f;
            break;
        case PreferredSize::Type::RATIO:
            return std::min(maxSize.width.resolve(parentWidth), std::max(preferredSize.width.Value, minSize.width.resolve(parentWidth))) * preferredSize.height.Value;
        }
        return std::min(maxSize.height.resolve(parentHeight), std::max(height, minSize.height.resolve(parentHeight)));
    }

    void Control::onMeasure(float parentWidth, float parentHeight) {
        measureWidth();
        measureHeight();
        /*[[likely]]
        if (preferredSize.width.Type != PreferredSize::Type::RATIO) {
            measuredSize.Width = resolveWidth(0, parentWidth, parentHeight);
            measuredSize.Height = resolveHeight(0, parentWidth, parentHeight);
        } else {
            measuredSize.Height = resolveHeight(0, parentWidth, parentHeight);
            measuredSize.Width = resolveWidth(0, parentWidth, parentHeight);
        }*/
    }

    bool Control::onMouseButtonEvent(const MouseButtonEventArgs& event) {
        if (focusable && event.Action == MouseAction::DOWN && !Focused) {
            requestFocus();
            return true;
        }
        return false;
    }

    Control* Control::resolvePath(const Array<AString>& path) {
        Control* result = this;
        for (const AString& part : path) {
            if (part == "Parent") {
                result = result->Parent;
            } else {
                result = result->find(part);
            }
            if (!result) {
                if (part == "parent") {
                    Logger::log(LogType::WARNING, _T("Could not find control 'parent', did you mean 'Parent'?\n"));
                } else {
                    Logger::log(LogType::WARNING, std::format(_T("Could not find control '{}'.\n"), part).c_str());
                }
                return nullptr;
            }
        }
        return result;
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
        if (Theme != theme) {
            localTheme = theme;
            dispatchThemeChanged();
        }
    }

    Theme* Control::getTheme() const {
        if (localTheme)
            return localTheme;
        if (parent)
            return parent->Theme;
        return nullptr;
    }

    IUIContext* Control::getContext() {
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
        onContextChanged();
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
        if (needsLayout || size.Width != width || size.Height != height) {
#ifdef _DEBUG
            /*const char* name = Name ? Name->Data : "[unnamed]";
            if (width < minSize.width || height < minSize.height)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is smaller than minSize\n", Type.Name, name);
            if (width == 0 || height == 0)
                Logger::log(LogType::INFO, "Control's ({}: {}) size is [0, 0]\n", Type.Name, name);*/
#endif
            size.Width = width;
            size.Height = height;
            needsLayout = false;
            onLayout(x, y, size.Width, size.Height);
            sizeChanged();
        }
    }

    void Control::draw(ICanvas& canvas) {
        if (size.Width == 0 || size.Height == 0)
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

    Control* Control::find(const AString& name, bool deep) {
        return nullptr;
    }

    Control* Control::find(const Ghurund::Core::Type& type, bool deep) {
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
        IUIContext* context = Context;
        if (!context)
            return pos;
        Window& window = context->Window;
        POINT p = { (LONG)pos.x, (LONG)pos.y };
        //ClientToScreen(window.Handle, &p);
        return FloatPoint{ (float)p.x, (float)p.y };
    }

    bool Control::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
        bool result = __super::dispatchMouseMotionEvent(event);
        if (!result && cursor) {
            cursor->set();
            return true;
        }
        return result;
    }

    void Control::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
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
            try {
                preferredSize = PreferredSize::parse(size);
            } catch (std::invalid_argument e) {}
        }
        auto widthAttr = xml.FindAttribute("width");
        if (widthAttr)
            width = std::unique_ptr<Constraint>(loader.loadConstraint(widthAttr->Value()));
        auto heightAttr = xml.FindAttribute("height");
        if (heightAttr)
            height = std::unique_ptr<Constraint>(loader.loadConstraint(heightAttr->Value()));
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
        auto leftAttr = xml.FindAttribute("left");
        if (leftAttr)
            Left = std::unique_ptr<Constraint>(loader.loadConstraint(leftAttr->Value()));
        auto topAttr = xml.FindAttribute("top");
        if (topAttr)
            Top = std::unique_ptr<Constraint>(loader.loadConstraint(topAttr->Value()));
        auto rightAttr = xml.FindAttribute("right");
        if (rightAttr)
            Right = std::unique_ptr<Constraint>(loader.loadConstraint(rightAttr->Value()));
        auto bottomAttr = xml.FindAttribute("bottom");
        if (bottomAttr)
            Bottom = std::unique_ptr<Constraint>(loader.loadConstraint(bottomAttr->Value()));
        auto styleAttr = xml.FindAttribute("style");
        if (styleAttr) {
            AString s = styleAttr->Value();
            s.replace('\\', '/');
            uint32_t value = 0;
            if (s.startsWith(LayoutLoader::THEME_STYLE)) {
                StyleKey styleKey = s.substring(lengthOf(LayoutLoader::THEME_STYLE));
                if (!loader.Theme) {
                    throw InvalidStateException("Loader does not have a theme set.");
                } else if (loader.Theme->Styles.containsKey(styleKey)) {
                    Style = loader.Theme->Styles[styleKey];
                } else {
                    Logger::log(LogType::WARNING, _T("Invalid style key '{}'. Default style for type '{}' will be used.\n"), styleKey.str, Type.Name);
                    Style = loader.Theme->Styles[StyleKey(Type.Name)];
                }
            }
        } else if (loader.Theme && loader.Theme->Styles.containsKey(StyleKey(Type.Name))) {
            Style = loader.Theme->Styles[StyleKey(Type.Name)];
        }
        auto childElement = xml.FirstChildElement();
        while (childElement) {
            if (strcmp(childElement->Name(), std::format("{}.Left", Type.Name).c_str()) == 0) {
                Left = std::unique_ptr<Constraint>(loader.loadConstraint(*childElement));
            } else if (strcmp(childElement->Name(), std::format("{}.Top", Type.Name).c_str()) == 0) {
                Top = std::unique_ptr<Constraint>(loader.loadConstraint(*childElement));
            } else if (strcmp(childElement->Name(), std::format("{}.Right", Type.Name).c_str()) == 0) {
                Right = std::unique_ptr<Constraint>(loader.loadConstraint(*childElement));
            } else if (strcmp(childElement->Name(), std::format("{}.Bottom", Type.Name).c_str()) == 0) {
                Bottom = std::unique_ptr<Constraint>(loader.loadConstraint(*childElement));
            } else if (strcmp(childElement->Name(), std::format("{}.Width", Type.Name).c_str()) == 0) {
                Width = std::unique_ptr<Constraint>(loader.loadConstraint(*childElement));
            } else if (strcmp(childElement->Name(), std::format("{}.Height", Type.Name).c_str()) == 0) {
                Height = std::unique_ptr<Constraint>(loader.loadConstraint(*childElement));
            }
            childElement = childElement->NextSiblingElement();
        }
    }

#ifdef _DEBUG
    void Control::validate() const {
        _ASSERTE(ReferenceCount < 1000);
        _ASSERTE(!parent || parent->ReferenceCount < 1000);
    }

    String Control::printTree() const {
        if (Name) {
            return String(std::format(_T("{} '{}' {}\n"), Type.Name, *Name, Size).c_str());
        } else {
            return String(std::format(_T("{} {}\n"), Type.Name, Size).c_str());
        }
    }
#endif
}
