#pragma once

#include "ChildrenProvider.h"
#include "ControlParent.h"

namespace Ghurund::UI {
	class ListControlProvider:public ControlProvider {
	private:
		List<Control*> children;
		ControlParent& owner;

	public:
		ListControlProvider(ControlParent& owner):owner(owner) {}

		~ListControlProvider() {
			clear();
		}

		inline void add(Control* control) {
			control->addReference();
			children.add(control);
			control->Parent = &owner;
		}

		inline void addAll(const List<Control*>& controls) {
			for (Control* control : controls)
				add(control);
		}

		inline void addAll(const std::initializer_list<Control*>& controls) {
			for (Control* control : controls)
				add(control);
		}

		inline void insert(size_t i, Control* control) {
			control->addReference();
			children.insert(i, control);
			control->Parent = &owner;
		}

		inline void remove(Control* control) {
			control->clearFocus();
			control->Parent = nullptr;
			control->release();
			children.removeAt(indexOf(control));
		}

		inline void removeAt(size_t index) {
			auto& c = children.get(index);
			c->clearFocus();
			c->Parent = nullptr;
			c->release();
			children.removeAt(index);
		}

		inline void clear() {
			for (Control* child : children) {
				child->clearFocus();
				child->Parent = nullptr;
				child->release();
			}
			children.clear();
		}

		inline ArrayIterator<Control*> begin() {
			return children.begin();
		}

		inline ConstArrayIterator<Control*> begin() const {
			return children.begin();
		}

		inline ArrayIterator<Control*> end() {
			return children.end();
		}

		inline ConstArrayIterator<Control*> end() const {
			return children.end();
		}

		virtual size_t getChildCount() const override {
			return children.getSize();
		}

		__declspec(property(get = getChildCount)) size_t ChildCount;

		inline void set(size_t i, Control* e) {
			Control* c = children[i];
			if (c == e)
				return;
			c->clearFocus();
			c->Parent = nullptr;
			c->release();
			e->addReference();
			children.set(i, c);
			c->Parent = &owner;
		}

		virtual Control* getChild(size_t i) override {
			return children.get(i);
		}

		inline size_t indexOf(const Control* control) const {
			return children.indexOf((Control*)control);
		}

		inline bool contains(const Control* control) const {
			return children.contains((Control*)control);
		}

		inline Control* operator[](size_t i)const {
			return children[i];
		}

		inline Control* find(const Ghurund::Core::AString& name) {
			for (Control* child : children) {
				if (child->Name && child->Name->operator==(name))
					return child;
			}
			return nullptr;
		}

		template<class T>
		inline T* find() const {
			return (T*)find(T::GET_TYPE());
		}

		inline Control* find(const Ghurund::Core::Type& type) const {
			for (Control* child : children) {
				if (child->Type == type)
					return child;
			}
			return nullptr;
		}
	};
}