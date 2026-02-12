#pragma once

#include "Component2D.h"

#include "core/Event.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class Component2DCollection {
	private:
		List<Component2D*> components;
		Component2D& owner;

	public:
		Event<Component2DCollection> collectionChanged = *this;

		Component2DCollection(Component2D& owner):owner(owner) {}

		~Component2DCollection() {
			clear();
		}

		inline void add(Component2D* component) {
			components.add(component);
			component->addReference();
			component->Parent = &owner;
			collectionChanged();
		}

		inline void addAll(const List<Component2D*>& components) {
			for (Component2D* component : components) {
				this->components.add(component);
				component->addReference();
				component->Parent = &owner;
			}
			collectionChanged();
		}

		inline void addAll(const std::initializer_list<Component2D*>& components) {
			for (Component2D* component : components) {
				this->components.add(component);
				component->addReference();
				component->Parent = &owner;
			}
			collectionChanged();
		}

		inline void insert(size_t i, Component2D* component) {
			components.insert(i, component);
			component->addReference();
			component->Parent = &owner;
			collectionChanged();
		}

		inline void remove(Component2D* component) {
			component->Parent = nullptr;
			components.remove(component);
			component->release();
			collectionChanged();
		}

		inline void removeAt(size_t index) {
			auto& component = components.get(index);
			component->Parent = nullptr;
			components.removeAt(index);
			component->release();
			collectionChanged();
		}

		inline void clear() {
			for (auto component : components)
				component->release();
			components.clear();
			collectionChanged();
		}

		inline ArrayIterator<Component2D*> begin() {
			return components.begin();
		}

		inline ConstArrayIterator<Component2D*> begin() const {
			return components.begin();
		}

		inline ArrayIterator<Component2D*> end() {
			return components.end();
		}

		inline ConstArrayIterator<Component2D*> end() const {
			return components.end();
		}

		virtual size_t getSize() const {
			return components.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, Component2D* e) {
			Component2D* component = components[i];
			if (component == e)
				return;
			component->Parent = nullptr;
			component->release();
			components.set(i, e);
			e->addReference();
			e->Parent = &owner;
			collectionChanged();
		}

		virtual Component2D* get(size_t i) {
			return components.get(i);
		}

		/*inline size_t indexOf(const Component2D* component) const {
			return components.indexOf(component);
		}

		inline bool contains(const Component2D* component) const {
			return components.contains(component);
		}*/

		inline Component2D* operator[](size_t i)const {
			return components[i];
		}

		inline size_t find(const Ghurund::Core::AString& name) {
			return components.find([&](Component2D* c) { return c->Name && c->Name->operator==(name); });
		}

		template<class T>
		inline T* find() const {
			return (T*)find(T::GET_TYPE());
		}

		inline size_t find(const Ghurund::Core::Type& type) const {
			return components.find([&](Component2D* c) { return c->Type == type; });
		}
	};
}