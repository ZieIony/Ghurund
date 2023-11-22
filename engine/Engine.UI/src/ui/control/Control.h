#pragma once

#include "Status.h"
#include "MouseEvents.h"
#include "core/resource/Resource.h"
#include "core/Event.h"
#include "core/math/Matrix3x2.h"
#include "core/math/Size.h"
#include "core/input/EventConsumer.h"
#include "ui/Cursor.h"
#include "ui/UIContext.h"
#include "ui/style/AttrProperty.h"
#include "ui/constraint/Constraint.h"
#include "ui/constraint/ConstraintSet.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/constraint/WrapConstraint.h"
#include "ui/constraint/FlowConstraint.h"
#include "ui/constraint/SelfConstraint.h"

namespace tinyxml2 {
	class XMLElement;
}

namespace Ghurund::Core {
	class ResourceManager;
}

namespace Ghurund::UI {
	class ControlParent;
	class Theme;
	class LayoutLoader;
	class ICanvas;
	class ConstraintGraph;

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

		void loadConstraints(LayoutLoader& loader, const tinyxml2::XMLElement& xml);

	protected:
		FloatPoint position = { 0,0 }, scale = { 1,1 };
		float rotation = 0;
		Ghurund::Core::Matrix3x2 transformation = {};

		Ghurund::Core::FloatSize measuredSize;  // what the view wants
		bool needsLayout = true;

		Theme* localTheme = nullptr;

		//List<Binding> bindings;

		SharedPointer<Constraint> left = SharedPointer<Constraint>(ghnew ValueConstraint(0.0f));
		SharedPointer<Constraint> width = SharedPointer<Constraint>(ghnew WrapWidthConstraint());
		SharedPointer<Constraint> right = SharedPointer<Constraint>(ghnew LeftWidthConstraint(left, width));
		SharedPointer<Constraint> top = SharedPointer<Constraint>(ghnew ValueConstraint(0.0f));
		SharedPointer<Constraint> height = SharedPointer<Constraint>(ghnew FlowHeightConstraint());
		SharedPointer<Constraint> bottom = SharedPointer<Constraint>(ghnew TopHeightConstraint(top, height));

		Control() {}

		Control(const Control& other):Resource(other),
			cursor(other.cursor),
			size(other.size),
			visible(other.visible), enabled(other.enabled), focusable(other.focusable), roundToPixels(other.roundToPixels),
			name(other.name ? ghnew AString(*other.name) : nullptr),
			position(other.position), rotation(other.rotation), transformation(other.transformation),
			measuredSize(other.measuredSize),
			needsLayout(other.needsLayout),
			localTheme(other.localTheme),
			left((Constraint*)other.left->clone()),
			width((Constraint*)other.width->clone()),
			right((Constraint*)other.right->clone()),
			top((Constraint*)other.top->clone()),
			height((Constraint*)other.height->clone()),
			bottom((Constraint*)other.bottom->clone()) {}

		virtual ~Control() = 0;

		virtual void loadInternal(Ghurund::UI::LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		virtual void onLoaded() {}

		virtual void onStateChanged() {}

		virtual void onThemeChanged() {}

		virtual void onContextChanged() {
			contextChanged();
		}

		virtual void onMeasure();

		virtual void onLayout(float x, float y, float width, float height) {}

		virtual void onDraw(ICanvas& canvas) {}

		virtual bool onMouseButtonEvent(const MouseButtonEventArgs& event) override;

		Control* resolvePath(const Array<AString>& path);

		virtual bool equalsImpl(const Object& other) const override;

	public:
		Event<Control> sizeChanged = *this;
		Event<Control> stateChanged = *this;
		Event<Control> themeChanged = *this;
		Event<Control> contextChanged = *this;

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
				dispatchStateChanged();
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

		virtual Control* getFocus() const {
			return nullptr;
		}

		__declspec(property(get = getFocus)) Control* Focus;

		inline Control* findFocus() const {
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

		/**
		* @brief Directional focus is useful when navigating with a gamepad.
		*/
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

		inline const Ghurund::Core::FloatSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) Ghurund::Core::FloatSize& Size;

		inline const Ghurund::Core::FloatSize& getMeasuredSize() const {
			return measuredSize;
		}

		__declspec(property(get = getMeasuredSize)) Ghurund::Core::FloatSize& MeasuredSize;

		inline bool canReceiveEvent(const KeyEventArgs& event) const {
			return Visible && Enabled;
		}

		inline bool canReceiveEvent(const MouseEventArgs& event) const {
			return Visible && Enabled && hitTest((float)event.Position.x, (float)event.Position.y);
		}

		// TODO: support matrix transformation
		inline bool hitTest(float x, float y) const {
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

		const Theme* getTheme() const;

		__declspec(property(get = getTheme, put = setTheme)) const Ghurund::UI::Theme* Theme;

		virtual IUIContext* getContext();

		__declspec(property(get = getContext)) IUIContext* Context;

		virtual void dispatchStateChanged() {
			stateChanged();
			onStateChanged();
		}

		virtual void dispatchThemeChanged() {
			themeChanged();
			onThemeChanged();
			dispatchStateChanged();
		}

		virtual void dispatchContextChanged();

		virtual void repaint();

		virtual void requestLayout();

		inline void measure() {
			onMeasure();
		}

		void layout(float x, float y, float width, float height);

		virtual void onUpdate(const uint64_t time) {}

		void draw(ICanvas& canvas);

		virtual Control* find(const Ghurund::Core::AString& name) {
			return (this->name && this->name->operator==(name)) ? this : nullptr;
		}

		template<class T>
		inline T* find() {
			return (T*)find(T::GET_TYPE());
		}

		virtual Control* find(const Ghurund::Core::Type& type) {
			return (Type == type) ? this : nullptr;
		}

		inline Constraint& getLeft() {
			return *left.get();
		}

		__declspec(property(get = getLeft)) Constraint& Left;

		inline Constraint& getRight() {
			return *right.get();
		}

		__declspec(property(get = getRight)) Constraint& Right;

		inline Constraint& getWidth() {
			return *width.get();
		}

		__declspec(property(get = getWidth)) Constraint& Width;

		inline Constraint& getTop() {
			return *top.get();
		}

		__declspec(property(get = getTop)) Constraint& Top;

		inline Constraint& getBottom() {
			return *bottom.get();
		}

		__declspec(property(get = getBottom)) Constraint& Bottom;

		inline Constraint& getHeight() {
			return *height.get();
		}

		__declspec(property(get = getHeight)) Constraint& Height;

		void setConstraints(const ConstraintSet& constraints);

		__declspec(property(put = setConstraints)) const ConstraintSet& Constraints;

		virtual void resolveConstraints(ConstraintGraph& graph);

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

		inline void load(Ghurund::UI::LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
			try {
				loadInternal(loader, workingDir, xml);
				onLoaded();
			} catch (std::exception e) {
				throw e;
			}
		}

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