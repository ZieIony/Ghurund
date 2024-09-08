#pragma once

#include "ControlParent.h"
#include "core/IntrusivePointer.h"

namespace Ghurund::UI {
	class ControlCollection {
	private:
		List<ControlWithConstraints> controls;
		ControlParent& owner;

	public:
		Event<ControlCollection> collectionChanged = *this;

		ControlCollection(ControlParent& owner):owner(owner) {}

		~ControlCollection() {
			clear();
		}

		inline void add(Control* control) {
			controls.add(ControlWithConstraints(control, owner.makeDefaultConstraints()));
			control->Parent = &owner;
			collectionChanged();
		}

		inline void add(Control* control, const ConstraintSet& constraints) {
			controls.add(ControlWithConstraints(control, constraints));
			control->Parent = &owner;
			collectionChanged();
		}

		inline void addAll(const List<Control*>& controls) {
			for (Control* control : controls) {
				this->controls.add(ControlWithConstraints(control, owner.makeDefaultConstraints()));
				control->Parent = &owner;
			}
			collectionChanged();
		}

		inline void addAll(const std::initializer_list<Control*>& controls) {
			for (Control* control : controls) {
				this->controls.add(ControlWithConstraints(control, owner.makeDefaultConstraints()));
				control->Parent = &owner;
			}
			collectionChanged();
		}

		inline void insert(size_t i, Control* control) {
			controls.insert(i, ControlWithConstraints(control, owner.makeDefaultConstraints()));
			control->Parent = &owner;
			collectionChanged();
		}

		inline void insert(size_t i, Control* control, const ConstraintSet& constraints) {
			controls.insert(i, ControlWithConstraints(control, constraints));
			control->Parent = &owner;
			collectionChanged();
		}

		inline void remove(Control* control) {
			control->clearFocus();
			control->Parent = nullptr;
			controls.removeAt(find(control));
			collectionChanged();
		}

		inline void removeAt(size_t index) {
			auto& c = controls.get(index);
			c.control->clearFocus();
			c.control->Parent = nullptr;
			controls.removeAt(index);
			collectionChanged();
		}

		inline void clear() {
			while(!controls.Empty){
				IntrusivePointer<Control> control = controls[0].control;
				controls.removeAt(0);
				control->clearFocus();
				control->Parent = nullptr;
			}
			collectionChanged();
		}

		inline ArrayIterator<ControlWithConstraints> begin() {
			return controls.begin();
		}

		inline ConstArrayIterator<ControlWithConstraints> begin() const {
			return controls.begin();
		}

		inline ArrayIterator<ControlWithConstraints> end() {
			return controls.end();
		}

		inline ConstArrayIterator<ControlWithConstraints> end() const {
			return controls.end();
		}

		virtual size_t getSize() const {
			return controls.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, Control* e) {
			ControlWithConstraints& c = controls[i];
			if (c.control.get() == e)
				return;
			c.control->clearFocus();
			c.control->Parent = nullptr;
			c.control->release();
			controls.set(i, ControlWithConstraints(e, owner.makeDefaultConstraints()));
			e->Parent = &owner;
			collectionChanged();
		}

		virtual ControlWithConstraints& get(size_t i) {
			return controls.get(i);
		}

		inline size_t find(const Control* control) const {
			return controls.find([&](ControlWithConstraints& c) { return c.control.get() == control; });
		}

		inline bool contains(const Control* control) const {
			return controls.find([&](ControlWithConstraints& c) { return c.control.get() == control; }) != controls.Size;
		}

		inline ControlWithConstraints& operator[](size_t i)const {
			return controls[i];
		}

		inline size_t find(const Ghurund::Core::AString& name) {
			return controls.find([&](ControlWithConstraints& c) { return c.control->Name && c.control->Name->operator==(name); });
		}

		template<class T>
		inline T* find() const {
			return (T*)find(T::GET_TYPE());
		}

		inline size_t find(const Ghurund::Core::Type& type) const {
			return controls.find([&](ControlWithConstraints& c) { return c.control->Type == type; });
		}
	};
}