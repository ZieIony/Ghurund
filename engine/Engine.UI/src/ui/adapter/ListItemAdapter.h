#pragma once

#include "ItemAdapter.h"

namespace Ghurund::UI {

	template<class T>
	class ListItemAdapter:public ItemAdapter {
		List<T> items;

	public:
		ListItemAdapter() {}

		ListItemAdapter(const List<T>& items):items(items) {}

		inline const List<T>& getItems() const {
			return items;
		}

		__declspec(property(get = getItems)) const List<T>& Items;

		virtual size_t getSize() const override {
			return items.Size;
		}
	};
}