#include "ghuipch.h"
#include "ControlParent.h"
#include "ControlGroup.h"

#include "core/input/Mouse.h"
#include "core/reflection/Property.h"
#include "core/reflection/UniqueProperty.h"
#include "core/reflection/StandardTypes.h"
#include "core/reflection/TypeBuilder.h"
#include "core/resource/ResourceManager.h"
#include "ui/Canvas.h"
#include "ui/Cursor.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/ParentConstraint.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/theme/Theme.h"

#include <regex>

namespace Ghurund::UI {

	const Ghurund::Core::Type& Control::GET_TYPE() {
		static auto PROPERTY_NAME = Property<Control, const AString*>("Name", (const AString * (Control::*)()) & getName, (void(Control::*)(const AString*)) & setName);
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
		static auto PROPERTY_MEASUREDSIZE = Property<Control, FloatSize&>("MeasuredSize", (FloatSize & (Control::*)()) & getMeasuredSize);
		static auto PROPERTY_PARENT = Property<Control, ControlParent*>("Parent", (ControlParent * (Control::*)()) & getParent, (void(Control::*)(ControlParent*)) & setParent);
		static auto PROPERTY_CURSOR = Property<Control, const Ghurund::UI::Cursor*>("Cursor", (Ghurund::UI::Cursor * (Control::*)()) & getCursor, (void(Control::*)(const Ghurund::UI::Cursor*)) & setCursor);
		static auto PROPERTY_THEME = Property<Control, Ghurund::UI::Theme*>("Theme", (Ghurund::UI::Theme * (Control::*)()) & getTheme, (void(Control::*)(Ghurund::UI::Theme*)) & setTheme);
		static auto PROPERTY_CONTEXT = Property<Control, IUIContext*>("Context", &getContext);
		static auto PROPERTY_POSITIONINWINDOW = Property<Control, FloatPoint>("PositionInWindow", &getPositionInWindow);
		static auto PROPERTY_POSITIONONSCREEN = Property<Control, FloatPoint>("PositionOnScreen", &getPositionOnScreen);

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
			.withProperty(PROPERTY_MEASUREDSIZE)
			.withProperty(PROPERTY_PARENT)
			.withProperty(PROPERTY_CURSOR)
			.withProperty(PROPERTY_THEME)
			.withProperty(PROPERTY_CONTEXT)
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

	void Control::loadInternal(LayoutLoader& loader, const DirectoryPath& workingDir, const tinyxml2::XMLElement& xml) {
		loader.loadProperties(*this, workingDir, xml);
		loadConstraints(loader, xml);
	}

	void Control::onMeasure() {
		measuredSize.Width = constraints.width->Value;
		measuredSize.Height = constraints.height->Value;
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

	bool Control::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const Control& c = (const Control&)other;
		return cursor == c.cursor &&
			size == c.size &&
			visible == c.visible && enabled == c.enabled && focusable == c.focusable && roundToPixels == c.roundToPixels &&
			name == c.name &&
			position == c.position, rotation == c.rotation && transformation == c.transformation &&
			measuredSize == c.measuredSize &&
			needsLayout == c.needsLayout &&
			localTheme == c.localTheme &&
			constraints == c.constraints;
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
		Control* c = Focus;
		while (c) {
			Control* f = c->Focus;
			c->Parent->Focus = nullptr;
			c = f;
		}
		// clear focus of this control's parent and its parents
		if (parent) {
			ControlParent* p = parent;
			while (true) {
				p->Focus = nullptr;
				if (!p->Parent)
					break;
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

	IUIContext* Control::getContext() {
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
		if (width > 1000) {
			int a = 5;
		}
		if (needsLayout || size.Width != width || size.Height != height) {
#ifdef _DEBUG
			const char* name = Name ? Name->Data : "[unnamed]";
			if (width == 0 || height == 0) {
				auto message = std::format(_T("Control's ({}: {}) size is [0, 0]\n"), Type.Name, AString(name));
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

	void Control::setConstraints(const ConstraintSet& constraints) {
		if (constraints.left != nullptr && constraints.width != nullptr && constraints.right != nullptr) {
			this->constraints.width = constraints.width.get();
			this->constraints.left.set(ghnew CenterLeftConstraint(constraints.left.get(), this->constraints.width, constraints.right.get()));
			this->constraints.right.set(ghnew CenterRightConstraint(constraints.left.get(), this->constraints.width, constraints.right.get()));
		} else if (constraints.left != nullptr) {
			this->constraints.left = constraints.left.get();
			if (constraints.width != nullptr) {
				this->constraints.width = constraints.width.get();
				this->constraints.right.set(ghnew LeftWidthConstraint(this->constraints.left, this->constraints.width));
			} else if (constraints.right != nullptr) {
				this->constraints.right = constraints.right.get();
				this->constraints.width.set(ghnew LeftRightConstraint(this->constraints.left, this->constraints.right));
			} else {
				this->constraints.width.set(ghnew WrapWidthConstraint());
				this->constraints.right.set(ghnew LeftWidthConstraint(this->constraints.left, this->constraints.width));
			}
		} else if (constraints.width != nullptr) {
			if (constraints.right != nullptr) {
				this->constraints.width = constraints.width.get();
				this->constraints.right = constraints.right.get();
				this->constraints.left.set(ghnew WidthRightConstraint(this->constraints.width, this->constraints.right));
			} else {
				this->constraints.left.set(ghnew ParentLeftConstraint());
				this->constraints.width = constraints.width.get();
				this->constraints.right.set(ghnew LeftWidthConstraint(this->constraints.left, this->constraints.width));
			}
		} else if (constraints.right != nullptr) {
			this->constraints.width.set(ghnew WrapWidthConstraint());
			this->constraints.right = constraints.right.get();
			this->constraints.left.set(ghnew WidthRightConstraint(this->constraints.width, this->constraints.right));
		} else {
			this->constraints.left.set(ghnew ParentLeftConstraint());
			this->constraints.width.set(ghnew WrapWidthConstraint());
			this->constraints.right.set(ghnew LeftWidthConstraint(this->constraints.left, this->constraints.width));
		}
		if (constraints.top != nullptr && constraints.height != nullptr && constraints.bottom != nullptr) {
			this->constraints.height = constraints.height.get();
			this->constraints.top.set(ghnew CenterTopConstraint(constraints.top.get(), this->constraints.height, constraints.bottom.get()));
			this->constraints.bottom.set(ghnew CenterBottomConstraint(constraints.top.get(), this->constraints.height, constraints.bottom.get()));
		} else if (constraints.top != nullptr) {
			this->constraints.top = constraints.top.get();
			if (constraints.height != nullptr) {
				this->constraints.height = constraints.height.get();
				this->constraints.bottom.set(ghnew TopHeightConstraint(this->constraints.top, this->constraints.height));
			} else if (constraints.bottom != nullptr) {
				this->constraints.bottom = constraints.bottom.get();
				this->constraints.height.set(ghnew TopBottomConstraint(this->constraints.top, this->constraints.bottom));
			} else {
				this->constraints.height.set(ghnew WrapHeightConstraint());
				this->constraints.bottom.set(ghnew TopHeightConstraint(this->constraints.top, this->constraints.height));
			}
		} else if (constraints.height != nullptr) {
			if (constraints.bottom != nullptr) {
				this->constraints.height = constraints.height.get();
				this->constraints.bottom = constraints.bottom.get();
				this->constraints.top.set(ghnew HeightBottomConstraint(this->constraints.height, this->constraints.bottom));
			} else {
				this->constraints.top.set(ghnew ParentTopConstraint());
				this->constraints.height = constraints.height.get();
				this->constraints.bottom.set(ghnew TopHeightConstraint(this->constraints.top, this->constraints.height));
			}
		} else if (constraints.bottom != nullptr) {
			this->constraints.height.set(ghnew WrapHeightConstraint());
			this->constraints.bottom = constraints.bottom.get();
			this->constraints.top.set(ghnew HeightBottomConstraint(this->constraints.height, this->constraints.bottom));
		} else {
			this->constraints.top.set(ghnew ParentTopConstraint());
			this->constraints.height.set(ghnew WrapHeightConstraint());
			this->constraints.bottom.set(ghnew TopHeightConstraint(this->constraints.top, this->constraints.height));
		}
	}

	void Control::resolveConstraints(ConstraintGraph& graph) {
		this->constraints.width->resolve(*this, graph);
		this->constraints.height->resolve(*this, graph);
		this->constraints.left->resolve(*this, graph);
		this->constraints.top->resolve(*this, graph);
		this->constraints.right->resolve(*this, graph);
		this->constraints.bottom->resolve(*this, graph);
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

	void Control::loadConstraints(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
		auto childElement = xml.FirstChildElement();
		const tinyxml2::XMLElement* leftElement = nullptr, * rightElement = nullptr, * widthElement = nullptr;
		const tinyxml2::XMLElement* topElement = nullptr, * bottomElement = nullptr, * heightElement = nullptr;
		while (childElement) {
			if (strcmp(childElement->Name(), std::format("{}.Left", Type.Name).c_str()) == 0) {
				leftElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Right", Type.Name).c_str()) == 0) {
				rightElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Width", Type.Name).c_str()) == 0) {
				widthElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Top", Type.Name).c_str()) == 0) {
				topElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Bottom", Type.Name).c_str()) == 0) {
				bottomElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Height", Type.Name).c_str()) == 0) {
				heightElement = childElement->ToElement();
			}
			childElement = childElement->NextSiblingElement();
		}
		auto leftAttr = xml.FindAttribute("left");
		auto rightAttr = xml.FindAttribute("right");
		auto widthAttr = xml.FindAttribute("width");
		auto topAttr = xml.FindAttribute("top");
		auto bottomAttr = xml.FindAttribute("bottom");
		auto heightAttr = xml.FindAttribute("height");

		if (leftAttr && leftElement)
			throw InvalidDataException(std::format("A combination of both - 'left' attribute and '{}.Left' child is invalid.", Type.Name).c_str());
		if (rightAttr && rightElement)
			throw InvalidDataException(std::format("A combination of both - 'right' attribute and '{}.Right' child is invalid.", Type.Name).c_str());
		if (widthAttr && widthElement)
			throw InvalidDataException(std::format("A combination of both - 'width' attribute and '{}.Width' child is invalid.", Type.Name).c_str());
		if (topAttr && topElement)
			throw InvalidDataException(std::format("A combination of both - 'top' attribute and '{}.Top' child is invalid.", Type.Name).c_str());
		if (bottomAttr && bottomElement)
			throw InvalidDataException(std::format("A combination of both - 'bottom' attribute and '{}.Bottom' child is invalid.", Type.Name).c_str());
		if (heightAttr && heightElement)
			throw InvalidDataException(std::format("A combination of both - 'height' attribute and '{}.Height' child is invalid.", Type.Name).c_str());

		SharedPointer<Constraint> left, right, width;
		SharedPointer<Constraint> top, bottom, height;
		if (leftElement) {
			left.set(loader.loadConstraint(*leftElement, Orientation::HORIZONTAL));
		} else  if (leftAttr) {
			left.set(loader.loadConstraint(leftAttr->Value(), Orientation::HORIZONTAL));
		}
		if (rightElement) {
			right.set(loader.loadConstraint(*rightElement, Orientation::HORIZONTAL));
		} else if (rightAttr) {
			right.set(loader.loadConstraint(rightAttr->Value(), Orientation::HORIZONTAL));
		}
		if (widthElement) {
			width.set(loader.loadConstraint(*widthElement, Orientation::HORIZONTAL));
		} else if (widthAttr) {
			width.set(loader.loadConstraint(widthAttr->Value(), Orientation::HORIZONTAL));
		}
		if (topElement) {
			top.set(loader.loadConstraint(*topElement, Orientation::VERTICAL));
		} else if (topAttr) {
			top.set(loader.loadConstraint(topAttr->Value(), Orientation::VERTICAL));
		}
		if (bottomElement) {
			bottom.set(loader.loadConstraint(*bottomElement, Orientation::VERTICAL));
		} else if (bottomAttr) {
			bottom.set(loader.loadConstraint(bottomAttr->Value(), Orientation::VERTICAL));
		}
		if (heightElement) {
			height.set(loader.loadConstraint(*heightElement, Orientation::VERTICAL));
		} else if (heightAttr) {
			height.set(loader.loadConstraint(heightAttr->Value(), Orientation::VERTICAL));
		}
		setConstraints({
			left,width,right,
			top,height,bottom
			});
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
		if (Name) {
			return String(std::format(_T("{} '{}' size: {}, state: {}\n"), Type.Name, *Name, Size, state).c_str());
		} else {
			return String(std::format(_T("{} size: {}, state: {}\n"), Type.Name, Size, state).c_str());
		}
	}
#endif
}
