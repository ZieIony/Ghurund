#pragma once

#include "core/Event.h"
#include "core/object/NotNull.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<typename T>
	class NamedIntrusiveOrderedObservableCollection {
	private:
		List<T*> items;

	public:
		Event<NamedIntrusiveOrderedObservableCollection, void> collectionChanged = *this;

		~NamedIntrusiveOrderedObservableCollection() {
			clear();
		}

		inline void add(NotNull<T> item) {
			item->addReference();
			items.add(item.get());
			collectionChanged();
		}

		inline void addAll(const List<T*>& items) {
			for (T* item : items) {
				item->addReference();
				this->items.add(item);
			}
			collectionChanged();
		}

		inline void addAll(const std::initializer_list<T*>& items) {
			for (T* item : items) {
				item->addReference();
				this->items.add(item);
			}
			collectionChanged();
		}

		inline void insert(size_t i, NotNull<T> item) {
			item->addReference();
			items.insert(i, item.get());
			collectionChanged();
		}

		inline void remove(T* item) {
			items.remove(item);
			item->release();
			collectionChanged();
		}

		inline void removeAt(size_t index) {
			auto& item = items.get(index);
			items.removeAt(index);
			item->release();
			collectionChanged();
		}

		inline void clear() {
			for (auto item : items)
				item->release();
			items.clear();
			collectionChanged();
		}

		inline ArrayIterator<T*> begin() {
			return items.begin();
		}

		inline ConstArrayIterator<T*> begin() const {
			return items.begin();
		}

		inline ArrayIterator<T*> end() {
			return items.end();
		}

		inline ConstArrayIterator<T*> end() const {
			return items.end();
		}

		inline size_t getSize() const {
			return items.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, T* e) {
			T* item = items[i];
			if (item == e)
				return;
			item->release();
			items.set(i, e);
			e->addReference();
			collectionChanged();
		}

		inline T* get(size_t i) {
			return items.get(i);
		}

		template<typename T>
		inline T* get() {
			for (auto& item : items) {
				if (item->Type.isOrExtends(T::TYPE))
					return (T*)item;
			}
			return nullptr;
		}

		template<typename T>
		inline T* get(size_t i) {
			size_t found = 0;
			for (auto& item : items) {
				if (item->Type.isOrExtends(T::TYPE))
					found++;
				if (found == i)
					return (T*)item;
			}
			return nullptr;
		}

		/*inline size_t indexOf(const T* item) const {
			return items.indexOf(item);
		}

		inline bool contains(const T* item) const {
			return items.contains(item);
		}*/

		inline T* operator[](size_t i)const {
			return items[i];
		}

		inline size_t find(const Ghurund::Core::AString& name) {
			return items.find([&](T* c) { return c->Name && c->Name->operator==(name); });
		}

		template<class T>
		inline T* find() const {
			return (T*)find(T::GET_TYPE());
		}

		inline size_t find(const Ghurund::Core::Type& type) const {
			return items.find([&](T* c) { return c->Type == type; });
		}
	};
}
