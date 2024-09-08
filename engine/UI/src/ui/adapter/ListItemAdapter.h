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

		inline void setItems(const List<T>& items) {
			this->items = items;
		}

		__declspec(property(get = getItems, put = setItems)) const List<T>& Items;

		virtual size_t getSize() const override {
			return items.Size;
		}
	};
}