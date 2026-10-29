#pragma once

#include "Animation.h"

#include "core/resource/Resource.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	template<Derived<Animation> T>
	class AnimationSet:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<AnimationSet>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = AnimationSet::GET_TYPE();
#pragma endregion

	private:
		List<T*> animations;

		inline void updateDataSize() {
			dataSize.system = sizeof(*this) + sizeof(T*) * animations.Capacity;
		}

	public:
		~AnimationSet() {
			clear();
		}

		inline void add(T* animation) {
			animations.add(animation);
			animation->addReference();
			updateDataSize();
			State = ResourceState::INITIALIZED;
		}

		inline void addAll(const List<T*>& animations) {
			for (T* animation : animations) {
				this->animations.add(animation);
				animation->addReference();
			}
			updateDataSize();
			State = ResourceState::INITIALIZED;
		}

		inline void addAll(const std::initializer_list<T*>& animations) {
			for (T* animation : animations) {
				this->animations.add(animation);
				animation->addReference();
			}
			updateDataSize();
			State = ResourceState::INITIALIZED;
		}

		inline void insert(size_t i, T* animation) {
			animations.insert(i, animation);
			animation->addReference();
			updateDataSize();
			State = ResourceState::INITIALIZED;
		}

		inline void remove(T* animation) {
			animations.remove(animation);
			animation->release();
			updateDataSize();
			if (animations.IsEmpty)
				State = ResourceState::EMPTY;
		}

		inline void removeAt(size_t index) {
			auto& animation = animations.get(index);
			animations.removeAt(index);
			animation->release();
			updateDataSize();
			if (animations.IsEmpty)
				State = ResourceState::EMPTY;
		}

		inline void clear() {
			for (auto animation : animations)
				animation->release();
			animations.clear();
			updateDataSize();
			State = ResourceState::EMPTY;
		}

		inline ArrayIterator<T*> begin() {
			return animations.begin();
		}

		inline ConstArrayIterator<T*> begin() const {
			return animations.begin();
		}

		inline ArrayIterator<T*> end() {
			return animations.end();
		}

		inline ConstArrayIterator<T*> end() const {
			return animations.end();
		}

		inline size_t getSize() const {
			return animations.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, T* e) {
			T* animation = animations[i];
			if (animation == e)
				return;
			animation->release();
			animations.set(i, e);
			e->addReference();
		}

		inline void set(const Ghurund::Core::WString& name, T* e) {
			size_t i = animations.find(name);
			T* animation = animations[i];
			if (animation == e)
				return;
			animation->release();
			animations.set(i, e);
			e->addReference();
		}

		inline T* get(size_t i) {
			return animations.get(i);
		}

		inline T* get(const Ghurund::Core::WString& name) {
			return animations.get(find(name));
		}

		/*inline size_t indexOf(const T* animation) const {
			return animations.indexOf(animation);
		}

		inline bool contains(const T* animation) const {
			return animations.contains(animation);
		}*/

		inline T* operator[](size_t i)const {
			return animations[i];
		}

		inline size_t find(const Ghurund::Core::WString& name) {
			return animations.find([&](T* c) { return c->Name&& c->Name->operator==(name); });
		}
	};
}
