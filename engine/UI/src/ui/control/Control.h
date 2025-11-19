#pragma once

#include "core/Event.h"
#include "core/input/EventConsumer.h"
#include "core/math/Matrix.h"
#include "core/math/Size.h"
#include "core/resource/Resource.h"
#include "ui/Binding.h"
#include "ui/constraint/Constraint.h"
#include "ui/constraint/ContentSize.h"
#include "ui/constraint/WrapConstraint.h"
#include "ui/UIContext.h"

namespace tinyxml2 {
	class XMLElement;
}

namespace Ghurund::Core {
	class Cursor;
	class ResourceManager;
}

namespace Ghurund::UI {
	class ControlParent;
	class Theme;
	class LayoutLoader;
	class ICanvas;
	class ConstraintGraph;

	using namespace Ghurund::Core;

	class Control:public Resource, public EventConsumer {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Control::GET_TYPE();
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
		ContentSize contentSize = Ghurund::UI::ContentSize(makeIntrusive<WrapWidthConstraint>().get(), makeIntrusive<WrapHeightConstraint>().get());
		Ghurund::Core::FloatSize minSize = { 0, 0 };
		Ghurund::Core::FloatSize maxSize = { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
		XMFLOAT2 position = { 0,0 }, scale = { 1,1 };
		float rotation = 0;
		Ghurund::Core::Matrix3x2 transformation = {};

		bool needsLayout = true;

		Theme* localTheme = nullptr;

		List<Binding> bindings;

		Control() {}

		Control(const Control& other):Resource(other),
			cursor(other.cursor),
			size(other.size),
			visible(other.visible), enabled(other.enabled), focusable(other.focusable), roundToPixels(other.roundToPixels),
			name(other.name ? ghnew AString(*other.name) : nullptr),
			position(other.position), rotation(other.rotation), transformation(other.transformation),
			needsLayout(other.needsLayout),
			localTheme(other.localTheme) {}

		virtual ~Control() = 0;

		virtual void loadInternal(Ghurund::UI::LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml);

		virtual void onLoaded() {}

		virtual void onStateChanged() {}

		virtual void onThemeChanged() {}

		virtual void onContextChanged() {
			contextChanged();
		}

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

		inline const XMFLOAT2& getPosition() const {
			return position;
		}

		inline void setPosition(const XMFLOAT2& position) {
			this->position = position;
		}

		inline void setPosition(float x, float y) {
			position.x = x;
			position.y = y;
		}

		__declspec(property(get = getPosition, put = setPosition)) const XMFLOAT2& Position;

		inline float getRotation() const {
			return rotation;
		}

		inline void setRotation(float rotation) {
			this->rotation = rotation;
		}

		__declspec(property(get = getRotation, put = setRotation)) float Rotation;

		inline const XMFLOAT2& getScale() const {
			return scale;
		}

		inline void setScale(const XMFLOAT2& scale) {
			this->scale = scale;
		}

		inline void setScale(float x, float y) {
			position.x = x;
			position.y = y;
		}

		__declspec(property(get = getScale, put = setScale)) const XMFLOAT2& Scale;

		inline const Ghurund::Core::Matrix3x2& getTransformation() const {
			return transformation;
		}

		__declspec(property(get = getTransformation)) const Ghurund::Core::Matrix3x2& Transformation;

		inline ContentSize& getContentSize() {
			return contentSize;
		}

		__declspec(property(get = getContentSize)) ContentSize& ContentSize;

		inline const Ghurund::Core::FloatSize& getMinSize() const {
			return minSize;
		}

		__declspec(property(get = getMinSize)) Ghurund::Core::FloatSize& MinSize;

		inline const Ghurund::Core::FloatSize& getMaxSize() const {
			return maxSize;
		}

		__declspec(property(get = getMaxSize)) Ghurund::Core::FloatSize& MaxSize;

		inline const Ghurund::Core::FloatSize& getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) Ghurund::Core::FloatSize& Size;

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

		virtual void resolveConstraints(ConstraintGraph& graph, const Constraint& width, const Constraint& height) {
			contentSize.Width.resolve(*this, graph);
			contentSize.Height.resolve(*this, graph);
		}

		virtual void bind();

		virtual XMFLOAT2 getPositionInWindow();

		__declspec(property(get = getPositionInWindow)) XMFLOAT2 PositionInWindow;

		XMFLOAT2 getPositionOnScreen();

		__declspec(property(get = getPositionOnScreen)) XMFLOAT2 PositionOnScreen;

		virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override;

		inline void load(Ghurund::UI::LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
			try {
				loadInternal(loader, workingDir, xml);
				onLoaded();
			} catch (std::exception e) {
				throw e;
			}
		}

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return Control::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };
#pragma endregion

#ifdef _DEBUG
		virtual void validate() const;

		virtual String printTree() const;
#endif
	};

	template<class T>
	concept IsControl = std::is_base_of<Control, T>::value;
}