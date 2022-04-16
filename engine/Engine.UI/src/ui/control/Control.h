#pragma once

#include "Status.h"
#include "MouseEvents.h"
#include "core/resource/Resource.h"
#include "core/Event.h"
#include "core/math/Matrix3x2.h"
#include "core/math/Size.h"
#include "core/input/EventConsumer.h"
#include "ui/Cursor.h"
#include "ui/PreferredSize.h"
#include "ui/SizeConstraints.h"
#include "ui/UIContext.h"
#include "ui/style/Style.h"
#include "ui/layout/constraint/Constraint.h"
#include "ui/layout/constraint/ValueConstraint.h"
#include "ui/layout/constraint/WrapConstraint.h"

namespace tinyxml2 {
    class XMLElement;
}

namespace Ghurund::UI {
    class ControlParent;
    class Theme;
    class LayoutLoader;
    class ICanvas;
}

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class Control: public Resource, public EventConsumer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

    private:
        ControlParent* parent = nullptr;
        const Cursor* cursor = nullptr;

        Ghurund::Core::FloatSize size = { 0, 0 };  // what was finally mediated

        bool visible = true;
        bool enabled = true;
        bool focusable = false;
        bool roundToPixels = true;

        Ghurund::Core::AString* name = nullptr;

    protected:
        FloatPoint position = { 0,0 }, scale = { 1,1 };
        float rotation = 0;
        Ghurund::Core::Matrix3x2 transformation = {};

        SizeConstraints minSize = { 0,0 };
        SizeConstraints maxSize = { SizeConstraints::Width(SizeConstraints::Type::PERCENT, 100), SizeConstraints::Height(SizeConstraints::Type::PERCENT, 100) };
        PreferredSize preferredSize;   // what the user wants
        Ghurund::Core::FloatSize measuredSize;  // what the view wants
        bool needsLayout = true;

        Theme* localTheme = nullptr;
        const Style* style = nullptr;

        //List<Binding> bindings;

        std::shared_ptr<Constraint> left = std::make_shared<ValueConstraint>(0.0f);
        std::shared_ptr<Constraint> right = std::make_shared<LeftWidthConstraint>();
        std::shared_ptr<Constraint> width = std::make_shared<ValueConstraint>(0.0f);
        std::shared_ptr<Constraint> top = std::make_shared<ValueConstraint>(0.0f);
        std::shared_ptr<Constraint> bottom = std::make_shared<TopHeightConstraint>();
        std::shared_ptr<Constraint> height = std::make_shared<ValueConstraint>(0.0f);

        virtual void onStateChanged() {
            stateChanged();
            if (style)
                style->onStateChanged(*this);
        }

        virtual void onThemeChanged() {
            themeChanged();
            if (style)
                style->onThemeChanged(*this);
        }

        virtual void onContextChanged() {
            contextChanged();
        }

        virtual void onMeasure(float parentWidth, float parentHeight);

        virtual void onLayout(float x, float y, float width, float height) {}

        virtual void onDraw(ICanvas& canvas) {}

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

        Control* resolvePath(const Array<AString>& path);

        virtual ~Control()
            //    = 0   // TODO: a destructor cannot be abstract
            ;

    public:
        Event<Control> sizeChanged = Event<Control>(*this);
        Event<Control> stateChanged = Event<Control>(*this);
        Event<Control> themeChanged = Event<Control>(*this);
        Event<Control> contextChanged = Event<Control>(*this);

        Control() {
            /*left.reset(ghnew WidthValueConstraint(0));
            top.reset(ghnew HeightValueConstraint(0));
            right.reset(ghnew WidthValueConstraint(0));
            bottom.reset(ghnew HeightValueConstraint(0));
            width.reset(ghnew WidthWrapConstraint());
            height.reset(ghnew HeightWrapConstraint());*/
        }

        inline const Ghurund::Core::AString* getName() const {
            return name;
        }

        void setName(const Ghurund::Core::AString* name);

        void setName(const Ghurund::Core::AString& name);

        __declspec(property(get = getName, put = setName)) const Ghurund::Core::AString* Name;

        inline bool isVisible() const {
            return visible;
        }

        inline void setVisible(bool visible) {
            this->visible = visible;
            if (!visible && Focused) {
                clearFocus();
            } else {
                onStateChanged();
            }
        }

        __declspec(property(get = isVisible, put = setVisible)) bool Visible;

        bool isEnabled() const;

        inline void setEnabled(bool enabled) {
            if (this->enabled == enabled)
                return;
            this->enabled = enabled;
            if (!enabled && Focused)
                clearFocus();
            dispatchStateChanged();
        }

        __declspec(property(get = isEnabled, put = setEnabled)) bool Enabled;

        inline bool isFocusable() const {
            return enabled && visible && focusable;
        }

        inline void setFocusable(bool focusable) {
            this->focusable = focusable;
            if (!Focusable)
                clearFocus();
        }

        __declspec(property(get = isFocusable, put = setFocusable)) bool Focusable;

        virtual Control* getFocus() {
            return nullptr;
        }

        __declspec(property(get = getFocus)) Control* Focus;

        inline Control* findFocus() {
            Control* focus = Focus;
            if (focus) {
                while (focus->Focus)
                    focus = focus->Focus;
            }
            return focus;
        }

        void requestFocus();

        void clearFocus();

        virtual bool isFocused() const;

        __declspec(property(get = isFocused)) bool Focused;

        virtual bool focusNext();

        virtual bool focusPrevious();

        virtual bool focusUp();

        virtual bool focusDown();

        virtual bool focusLeft();

        virtual bool focusRight();

        inline bool isRoundToPixelsEnabled() const {
            return roundToPixels;
        }

        inline void setRoundToPixelsEnabled(bool roundToPixels) {
            this->roundToPixels = roundToPixels;
        }

        __declspec(property(get = isRoundToPixelsEnabled, put = setRoundToPixelsEnabled)) bool RoundToPixelsEnabled;

        inline const FloatPoint& getPosition() const {
            return position;
        }

        inline void setPosition(const FloatPoint& position) {
            this->position = position;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getPosition, put = setPosition)) const FloatPoint& Position;

        inline float getRotation() const {
            return rotation;
        }

        inline void setRotation(float rotation) {
            this->rotation = rotation;
        }

        __declspec(property(get = getRotation, put = setRotation)) float Rotation;

        inline const FloatPoint& getScale() const {
            return scale;
        }

        inline void setScale(const FloatPoint& scale) {
            this->scale = scale;
        }

        inline void setScale(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getScale, put = setScale)) const FloatPoint& Scale;

        inline const Ghurund::Core::Matrix3x2& getTransformation() const {
            return transformation;
        }

        __declspec(property(get = getTransformation)) const Ghurund::Core::Matrix3x2& Transformation;

        inline const SizeConstraints& getMinSize() const {
            return minSize;
        }

        inline void setMinSize(const SizeConstraints& size) {
            this->minSize = size;
        }

        __declspec(property(get = getMinSize, put = setMinSize)) const SizeConstraints& MinSize;

        inline const SizeConstraints& getMaxSize() const {
            return maxSize;
        }

        inline void setMaxSize(const SizeConstraints& size) {
            this->maxSize = size;
        }

        __declspec(property(get = getMaxSize, put = setMaxSize)) const SizeConstraints& MaxSize;

        inline const Ghurund::Core::FloatSize& getSize() const {
            return size;
        }

        __declspec(property(get = getSize)) Ghurund::Core::FloatSize& Size;

        inline const PreferredSize& getPreferredSize() const {
            return preferredSize;
        }

        inline PreferredSize& getPreferredSize() {
            return preferredSize;
        }

        inline void setPreferredSize(const PreferredSize& size) {
            this->preferredSize = size;
        }

        virtual void setPreferredSize(const PreferredSize::Width& width, const PreferredSize::Height& height) {
            preferredSize.width = width;
            preferredSize.height = height;
        }

        __declspec(property(get = getPreferredSize, put = setPreferredSize)) const Ghurund::UI::PreferredSize& PreferredSize;

        inline const Ghurund::Core::FloatSize& getMeasuredSize() const {
            return measuredSize;
        }

        __declspec(property(get = getMeasuredSize)) Ghurund::Core::FloatSize& MeasuredSize;

        inline bool canReceiveEvent(const MouseEventArgs& event) {
            return Visible && Enabled && hitTest((float)event.Position.x, (float)event.Position.y);
        }

        // TODO: support matrix transformation
        inline bool hitTest(float x, float y) {
            return x >= position.x && x < position.x + size.Width && y >= position.y && y < position.y + size.Height;
        }

        void setParent(ControlParent* parent);

        inline ControlParent* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent, put = setParent)) ControlParent* Parent;

        inline const Cursor* getCursor() {
            return cursor;
        }

        inline void setCursor(const Cursor* cursor) {
            this->cursor = cursor;
        }

        __declspec(property(get = getCursor, put = setCursor)) const Ghurund::UI::Cursor* Cursor;

        void setTheme(Theme* theme);

        Theme* getTheme() const;

        __declspec(property(get = getTheme, put = setTheme)) Ghurund::UI::Theme* Theme;

        virtual IUIContext* getContext();

        __declspec(property(get = getContext)) IUIContext* Context;

        inline void setStyle(const Style* style) {
            this->style = style;
            if (style) {
                style->apply(*this);
                style->onThemeChanged(*this);
                style->onStateChanged(*this);
            }
        }

        inline const Style* getStyle() {
            return style;
        }

        __declspec(property(get = getStyle, put = setStyle)) const Ghurund::UI::Style* Style;

        virtual void dispatchStateChanged();

        virtual void dispatchThemeChanged();

        virtual void dispatchContextChanged();

        virtual void repaint();

        virtual void invalidate();

        inline void measure(float parentWidth, float parentHeight) {
            //if (needsLayout || preferredSize.width.Type != PreferredSize::Type::PIXELS || preferredSize.height.Type != PreferredSize::Type::PIXELS)
            onMeasure(parentWidth, parentHeight);
        }

        inline void measureWidth() {
            measuredSize.Width = width->Value;
        }

        inline void measureHeight() {
            measuredSize.Height = height->Value;
        }

        float resolveWidth(float contentSize, float parentWidth, float parentHeight) const;

        float resolveHeight(float contentSize, float parentWidth, float parentHeight) const;

        void layout(float x, float y, float width, float height);

        virtual void onUpdate(const uint64_t time) {}

        void draw(ICanvas& canvas);

        virtual Control* find(const Ghurund::Core::AString& name, bool deep = true);

        template<class T>
        inline T* find(bool deep = true) {
            return (T*)find(T::GET_TYPE(), deep);
        }

        virtual Control* find(const Ghurund::Core::Type& type, bool deep = true);

        inline Constraint& getLeft() {
            return *left;
        }

        inline void setLeft(std::unique_ptr<Constraint> left) {
            if (left) {
                this->left.reset(left.release());
            } else {
                this->left.reset(ghnew RightWidthConstraint());
            }
        }

        __declspec(property(get = getLeft, put = setLeft)) Constraint& Left;

        inline Constraint& getRight() {
            return *right;
        }

        inline void setRight(std::unique_ptr<Constraint> right) {
            if (right) {
                this->right.reset(right.release());
            } else {
                this->right.reset(ghnew LeftWidthConstraint());
            }
        }

        __declspec(property(get = getRight, put = setRight)) Constraint& Right;

        inline Constraint& getWidth() {
            return *width;
        }

        inline void setWidth(std::unique_ptr<Constraint> width) {
            if (width) {
                this->width.reset(width.release());
            } else {
                this->width.reset(ghnew WrapConstraint());
            }
        }

        inline void setWidth(float width) {
            this->width.reset(ghnew ValueConstraint(width));
        }

        __declspec(property(get = getWidth, put = setWidth)) Constraint& Width;

        inline Constraint& getTop() {
            return *top;
        }

        inline void setTop(std::unique_ptr<Constraint> top) {
            if (top) {
                this->top.reset(top.release());
            } else {
                this->top.reset(ghnew ValueConstraint(0.0f));
            }
        }

        __declspec(property(get = getTop, put = setTop)) Constraint& Top;

        inline Constraint& getBottom() {
            return *bottom;
        }

        inline void setBottom(std::unique_ptr<Constraint> bottom) {
            if (bottom) {
                this->bottom.reset(bottom.release());
            } else {
                this->bottom.reset(ghnew TopHeightConstraint());
            }
        }

        __declspec(property(get = getBottom, put = setBottom)) Constraint& Bottom;

        inline Constraint& getHeight() {
            return *height;
        }

        inline void setHeight(std::unique_ptr<Constraint> height) {
            if (height) {
                this->height.reset(height.release());
            } else {
                this->width.reset(ghnew WrapConstraint());
            }
        }

        inline void setHeight(float height) {
            this->height.reset(ghnew ValueConstraint(height));
        }

        __declspec(property(get = getHeight, put = setHeight)) Constraint& Height;

        virtual void resolveConstraints(List<Constraint*>& constraints) {
            width->resolve(*this);
            constraints.add(width.get());
            height->resolve(*this);
            constraints.add(height.get());
            left->resolve(*this);
            constraints.add(left.get());
            top->resolve(*this);
            constraints.add(top.get());
            right->resolve(*this);
            constraints.add(right.get());
            bottom->resolve(*this);
            constraints.add(bottom.get());
        }

        virtual void bind() {
            /*for (Binding& b : bindings) {
                Control* result = resolvePath(b.Path);
            }*/
        }

        virtual FloatPoint getPositionInWindow();

        __declspec(property(get = getPositionInWindow)) FloatPoint PositionInWindow;

        FloatPoint getPositionOnScreen();

        __declspec(property(get = getPositionOnScreen)) FloatPoint PositionOnScreen;

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

        virtual void load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml);

        static const inline Ghurund::Core::ResourceFormat FORMAT_XML = Ghurund::Core::ResourceFormat(L"xml", true, true);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_XML };

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }

#ifdef _DEBUG
        virtual void validate() const;

        virtual String printTree() const;
#endif
    };

    template<class T>
    concept IsControl = std::is_base_of<Control, T>::value;
}