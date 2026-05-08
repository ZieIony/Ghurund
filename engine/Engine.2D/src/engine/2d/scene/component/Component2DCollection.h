#pragma once

#include "Component2D.h"

#include "core/Event.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class Component2DCollection {
	private:
		List<Component2D*> components;

	public:
		Event<Component2DCollection> collectionChanged = *this;

		~Component2DCollection() {
			clear();
		}

		inline void add(NotNull<Component2D> component) {
			components.add(component.get());
			component->addReference();
			collectionChanged();
		}

		inline void addAll(const List<Component2D*>& components) {
			for (Component2D* component : components) {
				this->components.add(component);
				component->addReference();
			}
			collectionChanged();
		}

		inline void addAll(const std::initializer_list<Component2D*>& components) {
			for (Component2D* component : components) {
				this->components.add(component);
				component->addReference();
			}
			collectionChanged();
		}

		inline void insert(size_t i, NotNull<Component2D> component) {
			components.insert(i, component.get());
			component->addReference();
			collectionChanged();
		}

		inline void remove(Component2D* component) {
			components.remove(component);
			component->release();
			collectionChanged();
		}

		inline void removeAt(size_t index) {
			auto& component = components.get(index);
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

		inline size_t getSize() const {
			return components.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, Component2D* e) {
			Component2D* component = components[i];
			if (component == e)
				return;
			component->release();
			components.set(i, e);
			e->addReference();
			collectionChanged();
		}

		inline Component2D* get(size_t i) {
			return components.get(i);
		}

		template<typename T>
		inline T* get() {
			for (auto& component : components) {
				if (component->Type.isOrExtends(T::TYPE))
					return (T*)component;
			}
			return nullptr;
		}

		template<typename T>
		inline T* get(size_t i) {
			size_t found = 0;
			for (auto& component : components) {
				if (component->Type.isOrExtends(T::TYPE))
					found++;
				if (found == i)
					return (T*)component;
			}
			return nullptr;
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
