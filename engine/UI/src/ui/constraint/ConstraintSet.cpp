#include "ghuipch.h"
#include "ConstraintSet.h"

#include "ui/Canvas.h"
#include "ui/constraint/ContentConstraint.h"
#include "ui/constraint/ParentConstraint.h"
#include "ui/constraint/SelfConstraint.h"
#include "ui/loading/LayoutLoader.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	void PartialConstraintSet::load(const Type& controlType, LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
		auto childElement = xml.FirstChildElement();
		const tinyxml2::XMLElement* leftElement = nullptr, * rightElement = nullptr, * widthElement = nullptr;
		const tinyxml2::XMLElement* topElement = nullptr, * bottomElement = nullptr, * heightElement = nullptr;
		while (childElement) {
			if (strcmp(childElement->Name(), std::format("{}.Left", controlType.Name).c_str()) == 0) {
				leftElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Right", controlType.Name).c_str()) == 0) {
				rightElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Width", controlType.Name).c_str()) == 0) {
				widthElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Top", controlType.Name).c_str()) == 0) {
				topElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Bottom", controlType.Name).c_str()) == 0) {
				bottomElement = childElement->ToElement();
			} else if (strcmp(childElement->Name(), std::format("{}.Height", controlType.Name).c_str()) == 0) {
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
			throw InvalidDataException(std::format("A combination of both - 'left' attribute and '{}.Left' child is invalid.", controlType.Name).c_str());
		if (rightAttr && rightElement)
			throw InvalidDataException(std::format("A combination of both - 'right' attribute and '{}.Right' child is invalid.", controlType.Name).c_str());
		if (widthAttr && widthElement)
			throw InvalidDataException(std::format("A combination of both - 'width' attribute and '{}.Width' child is invalid.", controlType.Name).c_str());
		if (topAttr && topElement)
			throw InvalidDataException(std::format("A combination of both - 'top' attribute and '{}.Top' child is invalid.", controlType.Name).c_str());
		if (bottomAttr && bottomElement)
			throw InvalidDataException(std::format("A combination of both - 'bottom' attribute and '{}.Bottom' child is invalid.", controlType.Name).c_str());
		if (heightAttr && heightElement)
			throw InvalidDataException(std::format("A combination of both - 'height' attribute and '{}.Height' child is invalid.", controlType.Name).c_str());

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
	}

	void PartialConstraintSet::merge(const PartialConstraintSet& other) {
		if (other.left != nullptr)
			left = other.left;
		if (other.width != nullptr)
			width = other.width;
		if (other.right != nullptr)
			right = other.right;
		if (other.top != nullptr)
			top = other.top;
		if (other.height != nullptr)
			height = other.height;
		if (other.bottom != nullptr)
			bottom = other.bottom;
	}

	void ConstraintSet::resolve(Control& control, ConstraintGraph& graph) {
		left->resolve(control, graph);
		width->resolve(control, graph);
		right->resolve(control, graph);
		top->resolve(control, graph);
		height->resolve(control, graph);
		bottom->resolve(control, graph);
	}

#ifdef _DEBUG
	void ConstraintSet::draw(ICanvas& canvas) {
		float x = left->Value, y = top->Value, w = right->Value - x, h = bottom->Value - y;
		left->draw(canvas, x, y, w, h);
		width->draw(canvas, x, y, w, h);
		right->draw(canvas, x, y, w, h);
		top->draw(canvas, x, y, w, h);
		height->draw(canvas, x, y, w, h);
		bottom->draw(canvas, x, y, w, h);
	}
#endif

	ConstraintSet::ConstraintSet(const PartialConstraintSet& set) {
		if (set.left != nullptr && set.width != nullptr && set.right != nullptr) {
			width = set.width;
			left.set(ghnew CenterLeftConstraint(set.left, width, set.right));
			right.set(ghnew CenterRightConstraint(set.left, width, set.right));
		} else if (set.left != nullptr) {
			left = set.left;
			if (set.width != nullptr) {
				width = set.width;
				right.set(ghnew LeftWidthConstraint(left, width));
			} else if (set.right != nullptr) {
				right = set.right;
				width.set(ghnew LeftRightConstraint(left, right));
			} else {
				width.set(ghnew ContentWidthConstraint());
				right.set(ghnew LeftWidthConstraint(left, width));
			}
		} else if (set.width != nullptr) {
			if (set.right != nullptr) {
				width = set.width;
				right = set.right;
				left.set(ghnew WidthRightConstraint(width, right));
			} else {
				left.set(ghnew ParentLeftConstraint());
				width = set.width;
				right.set(ghnew LeftWidthConstraint(left, width));
			}
		} else if (set.right != nullptr) {
			width.set(ghnew ContentWidthConstraint());
			right = set.right;
			left.set(ghnew WidthRightConstraint(width, right));
		} else {
			left.set(ghnew ParentLeftConstraint());
			width.set(ghnew ContentWidthConstraint());
			right.set(ghnew LeftWidthConstraint(left, width));
		}
		if (set.top != nullptr && set.height != nullptr && set.bottom != nullptr) {
			height = set.height;
			top.set(ghnew CenterTopConstraint(set.top, height, set.bottom));
			bottom.set(ghnew CenterBottomConstraint(set.top, height, set.bottom));
		} else if (set.top != nullptr) {
			top = set.top;
			if (set.height != nullptr) {
				height = set.height;
				bottom.set(ghnew TopHeightConstraint(top, height));
			} else if (set.bottom != nullptr) {
				bottom = set.bottom;
				height.set(ghnew TopBottomConstraint(top, bottom));
			} else {
				height.set(ghnew ContentHeightConstraint());
				bottom.set(ghnew TopHeightConstraint(top, height));
			}
		} else if (set.height != nullptr) {
			if (set.bottom != nullptr) {
				height = set.height;
				bottom = set.bottom;
				top.set(ghnew HeightBottomConstraint(height, bottom));
			} else {
				top.set(ghnew ParentTopConstraint());
				height = set.height;
				bottom.set(ghnew TopHeightConstraint(top, height));
			}
		} else if (set.bottom != nullptr) {
			height.set(ghnew ContentHeightConstraint());
			bottom = set.bottom;
			top.set(ghnew HeightBottomConstraint(height, bottom));
		} else {
			top.set(ghnew ParentTopConstraint());
			height.set(ghnew ContentHeightConstraint());
			bottom.set(ghnew TopHeightConstraint(top, height));
		}
	}
}