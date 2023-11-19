#pragma once

#include "ui/control/ControlContainerBase.h"
#include "ui/style/LayoutAttr.h"
#include "ui/style/PointerAttrProperty.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class Widget:public ControlContainerBase {
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

		PointerAttrProperty<LayoutAttr, Control> layout;

		Widget() {}

		Widget(const Widget& other):ControlContainerBase(other), layout(other.layout) {}

		void updateLayout();

		virtual void onLoaded() override;

		virtual void onThemeChanged() override;

		virtual void onLayoutChanged() {}

	public:
		inline static const Ghurund::Core::Type& TYPE = Widget::GET_TYPE();

		static const Ghurund::Core::Type& GET_TYPE();

		inline void setLayout(std::unique_ptr<LayoutAttr> layout) {
			this->layout.set(std::move(layout));
			updateLayout();
		}

		__declspec(property(put = setLayout)) LayoutAttr* Layout;
	};
}
