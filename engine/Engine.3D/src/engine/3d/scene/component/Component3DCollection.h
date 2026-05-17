#pragma once

#include "Component3D.h"

#include "core/Event.h"

namespace Ghurund::Engine::_3D {
	using namespace Ghurund::Core;

	class Component3DCollection {
	private:
		List<Component3D*> components;

	public:
		Event<Component3DCollection> collectionChanged = *this;

		~Component3DCollection() {
			clear();
		}

		inline void add(NotNull<Component3D> component) {
			components.add(component.get());
			component->addReference();
			collectionChanged();
		}

		inline void addAll(const List<Component3D*>& components) {
			for (Component3D* component : components) {
				this->components.add(component);
				component->addReference();
			}
			collectionChanged();
		}

		inline void addAll(const std::initializer_list<Component3D*>& components) {
			for (Component3D* component : components) {
				this->components.add(component);
				component->addReference();
			}
			collectionChanged();
		}

		inline void insert(size_t i, NotNull<Component3D> component) {
			components.insert(i, component.get());
			component->addReference();
			collectionChanged();
		}

		inline void remove(Component3D* component) {
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

		inline ArrayIterator<Component3D*> begin() {
			return components.begin();
		}

		inline ConstArrayIterator<Component3D*> begin() const {
			return components.begin();
		}

		inline ArrayIterator<Component3D*> end() {
			return components.end();
		}

		inline ConstArrayIterator<Component3D*> end() const {
			return components.end();
		}

		inline size_t getSize() const {
			return components.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, Component3D* e) {
			Component3D* component = components[i];
			if (component == e)
				return;
			component->release();
			components.set(i, e);
			e->addReference();
			collectionChanged();
		}

		inline Component3D* get(size_t i) {
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

		/*inline size_t indexOf(const Component3D* component) const {
			return components.indexOf(component);
		}

		inline bool contains(const Component3D* component) const {
			return components.contains(component);
		}*/

		inline Component3D* operator[](size_t i)const {
			return components[i];
		}

		inline size_t find(const Ghurund::Core::AString& name) {
			return components.find([&](Component3D* c) { return c->Name && c->Name->operator==(name); });
		}

		template<class T>
		inline T* find() const {
			return (T*)find(T::GET_TYPE());
		}

		inline size_t find(const Ghurund::Core::Type& type) const {
			return components.find([&](Component3D* c) { return c->Type == type; });
		}
	};
}
