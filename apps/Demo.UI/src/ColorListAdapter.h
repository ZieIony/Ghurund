#pragma once

#include "ui/adapter/ListItemAdapter.h"
#include <core/Color.h>
#include <ui/control/ControlGroup.h>

namespace Demo {
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;

	class ColorListAdapter:public ListItemAdapter<Color> {
	public:
		ColorListAdapter(const List<Color>& items):ListItemAdapter(items) {}

		virtual Control* makeControl(size_t type) const override {
			ControlGroup* group = ghnew ControlGroup();
			auto color = makeIntrusive<Control>();
			group->Children.add(color.get(), makeConstraints({
				.width = 100,
				.height = 50
				}));
			return group;
		}

		virtual void bind(Control& control, size_t position) const {
			//ColorView* colorView = control.find<ColorView>();
			//colorView->Color = ColorValue(Items[position].Value);
		}
	};

}