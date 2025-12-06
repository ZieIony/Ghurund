#include "ghuipch.h"

#include "ControlParent.h"

#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"
#include "core/window/Cursor.h"
#include "engine/graphics/RenderGroup.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/material/ControlMaterialParameters.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {

	const Ghurund::Core::Type& Control::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<Control>();
		static auto PROPERTY_NAME = Property<Control, const AString*>("Name", (const AString * (Control::*)()) & getName, (void(Control::*)(const AString*)) & setName);
		static auto PROPERTY_VISIBLE = Property<Control, bool>("Visible", (bool(Control::*)()) & isVisible, (void(Control::*)(bool)) & setVisible);
		static auto PROPERTY_ENABLED = Property<Control, bool>("Enabled", (bool(Control::*)()) & isEnabled, (void(Control::*)(bool)) & setEnabled);
		static auto PROPERTY_FOCUSABLE = Property<Control, bool>("Focusable", (bool(Control::*)()) & isFocusable, (void(Control::*)(bool)) & setFocusable);
		static auto PROPERTY_FOCUS = Property<Control, Control*>("Focus", &getFocus);
		static auto PROPERTY_FOCUSED = Property<Control, bool>("Focused", (bool(Control::*)()) & isFocused);
		static auto PROPERTY_POSITION = Property<Control, const XMFLOAT2&>("Position", (XMFLOAT2 & (Control::*)()) & getPosition, (void(Control::*)(const XMFLOAT2&)) & setPosition);
		static auto PROPERTY_SIZE = Property<Control, FloatSize&>("Size", (FloatSize & (Control::*)()) & getSize);
		static auto PROPERTY_PARENT = Property<Control, ControlParent*>("Parent", (ControlParent * (Control::*)()) & getParent, (void(Control::*)(ControlParent*)) & setParent);
		static auto PROPERTY_CURSOR = Property<Control, const Ghurund::UI::Cursor*>("Cursor", (Ghurund::UI::Cursor * (Control::*)()) & getCursor, (void(Control::*)(const Ghurund::UI::Cursor*)) & setCursor);
		static auto PROPERTY_MATERIAL = Property<Control, Ghurund::Engine::IMaterial*>("Material", & getMaterial, & setMaterial);
		static auto PROPERTY_THEME = Property<Control, Ghurund::UI::Theme*>("Theme", (Ghurund::UI::Theme * (Control::*)()) & getTheme, (void(Control::*)(Ghurund::UI::Theme*)) & setTheme);
		static auto PROPERTY_CONTEXT = Property<Control, UIContext*>("Context", &getContext);
		static auto PROPERTY_POSITIONINWINDOW = Property<Control, XMFLOAT2>("PositionInWindow", &getPositionInWindow);
		static auto PROPERTY_POSITIONONSCREEN = Property<Control, XMFLOAT2>("PositionOnScreen", &getPositionOnScreen);

		static const Ghurund::Core::Type TYPE = TypeBuilder<Control>()
			.withConstructor(CONSTRUCTOR)
			.withProperty(PROPERTY_NAME)
			.withProperty(PROPERTY_VISIBLE)
			.withProperty(PROPERTY_ENABLED)
			.withProperty(PROPERTY_FOCUSABLE)
			.withProperty(PROPERTY_FOCUS)
			.withProperty(PROPERTY_FOCUSED)
			.withProperty(PROPERTY_POSITION)
			.withProperty(PROPERTY_SIZE)
			.withProperty(PROPERTY_PARENT)
			.withProperty(PROPERTY_CURSOR)
			.withProperty(PROPERTY_MATERIAL)
			.withProperty(PROPERTY_THEME)
			.withProperty(PROPERTY_CONTEXT)
			.withProperty(PROPERTY_POSITIONINWINDOW)
			.withProperty(PROPERTY_POSITIONONSCREEN)
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

	void Control::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
		loader.loadProperties(*this, workingDir, xml);
		//loader.loadBindings()
	}

	void Control::onDraw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		if (material == nullptr)
			return;
		positionParameter->Value = parentPosition + position;
		sizeParameter->Value = { Size.Width, Size.Height };
		alphaParameter->Value = alpha;
		group.objects.add(DrawPacket{
			mesh,
			material,
			XMFLOAT3(parentPosition.x + position.x, parentPosition.y + position.y, 0)
		});
	}

	bool Control::onMouseButtonEvent(const MouseButtonEventArgs& event) {
		if (focusable && event.Action == MouseButtonAction::PRESSED && !Focused) {
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

	bool Control::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const Control& c = (const Control&)other;
		return cursor == c.cursor &&
			size == c.size &&
			visible == c.visible && enabled == c.enabled && focusable == c.focusable && roundToPixels == c.roundToPixels &&
			*name == *c.name &&
			position == c.position &&
			needsLayout == c.needsLayout &&
			localTheme == c.localTheme;
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
		// clear focus of this control and its children
		boolean childFocus = Focus != nullptr;
		Control* c = Focus;
		while (c) {
			Control* f = c->Focus;
			c->Parent->Focus = nullptr;
			c = f;
		}
		// clear focus of this control's parent and its parents
		if (parent) {
			if (parent->Focus != this)
				return;
			ControlParent* p = parent;
			while (true) {
				p->Focus = nullptr;
				if (!p->Parent)
					break;
				p = p->Parent;
			}
			p->dispatchStateChanged();
		} else if (childFocus) {
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
		if (Focused)
			clearFocus();
		this->parent = parent;
		if (contextChanged)
			dispatchContextChanged();
		if (themeChanged)
			dispatchThemeChanged();
	}

	void Control::setTheme(Ghurund::UI::Theme* theme) {
		const UI::Theme* previousTheme = Theme;
		localTheme = theme;
		const UI::Theme* currentTheme = Theme;
		if (previousTheme != currentTheme)
			dispatchThemeChanged();
	}

	const Theme* Control::getTheme() const {
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

	void Control::dispatchContextChanged() {
		onContextChanged();
	}

	void Control::repaint() {
		if (parent)
			parent->repaint();
	}

	void Control::requestLayout() {
		needsLayout = true;
		if (parent)
			parent->requestLayout();
	}

	void Control::layout(float x, float y, float width, float height) {
		if (position.x != x || position.y != y) {
			position.x = x;
			position.y = y;
		}
		if (needsLayout || size.Width != width || size.Height != height) {
#ifdef _DEBUG
			if (width == 0 || height == 0) {
				AString name = Name ? *Name : "[unnamed]";
				auto message = std::format(_T("Control's ({}: {}) size is [0, 0]\n"), Type.Name, name);
				Logger::log(LogType::INFO, message.c_str());
			}
#endif
			size.Width = width;
			size.Height = height;
			needsLayout = false;
			onLayout(x, y, size.Width, size.Height);
			sizeChanged();
		}
	}

	void Control::draw(RenderGroup& group, const XMFLOAT2& parentPosition) {
		if (size.Width == 0 || size.Height == 0)
			return;
#ifdef _DEBUG
		/*        if (!Theme) {
					Logger::log(LogType::WARNING, _T("cannot draw Control ({}: {}) because its theme is null\n"), Type.Name, Name ? *Name : String("[unnamed]"));
					return;
				}*/
#endif
		//canvas.translate(position.x, position.y);
		onDraw(group, parentPosition);
	}

	void Control::bind() {
		for (Binding& b : bindings) {
			b.execute();
		}
	}

	XMFLOAT2 Control::getPositionInWindow() {
		Control* control = this;
		while (control) {
			//matrix = matrix * control->Transformation;
			control = control->Parent;
		}
		//D2D1_POINT_2F p = { 0,0 };
		//matrix.TransformPoint(p);
		return XMFLOAT2{ 0, 0 };
	}

	XMFLOAT2 Control::getPositionOnScreen() {
		auto pos = PositionInWindow;
		UIContext* context = Context;
		if (!context)
			return pos;
		Window& window = context->Window;
		POINT p = { (LONG)pos.x, (LONG)pos.y };
		//ClientToScreen(window.Handle, &p);
		return XMFLOAT2{ (float)p.x, (float)p.y };
	}

	bool Control::dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
		bool result = __super::dispatchMouseMotionEvent(event);
		if (!result && cursor) {
			cursor->set();
			return true;
		}
		return result;
	}

#ifdef _DEBUG
	void Control::validate() const {
		_ASSERTE(ReferenceCount < 1000);
		_ASSERTE(!parent || parent->ReferenceCount < 1000);
	}

	String Control::printTree() const {
		String state = _T("");
		if (Enabled)
			state.add(_T('e'));
		if (Focusable)
			state.add(_T('f'));
		if (Focused)
			state.add(_T('F'));
		if (Visible)
			state.add(_T('v'));

		if (Parent) {
			auto& constraints = Parent->getConstraints(*this);
			auto s = std::format(
				_T("[{}: {}, {}: {}]"),
				constraints.Width.Type.Name, constraints.Width.Value,
				constraints.Height.Type.Name, constraints.Height.Value
			);
			if (Name) {
				return String(std::format(_T("{} '{}' size: {}, state: {}\n"), Type.Name, *Name, s, state).c_str());
			} else {
				return String(std::format(_T("{} size: {}, state: {}\n"), Type.Name, s, state).c_str());
			}
		} else {
			if (Name) {
				return String(std::format(_T("{} '{}', state: {}\n"), Type.Name, *Name, state).c_str());
			} else {
				return String(std::format(_T("{}, state: {}\n"), Type.Name, state).c_str());
			}
		}
	}
#endif
}
