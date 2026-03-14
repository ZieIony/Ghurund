#pragma once

#include "SpriteAnimation.h"

#include "core/resource/Resource.h"

namespace Ghurund::Engine::_2D {
	using namespace Ghurund::Core;

	class SpriteAnimationSet:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<SpriteAnimationSet>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = SpriteAnimationSet::GET_TYPE();
#pragma endregion

	private:
		List<SpriteAnimation*> animations;

	public:
		~SpriteAnimationSet() {
			clear();
		}

		inline void add(SpriteAnimation* animation) {
			animations.add(animation);
			animation->addReference();
		}

		inline void addAll(const List<SpriteAnimation*>& animations) {
			for (SpriteAnimation* animation : animations) {
				this->animations.add(animation);
				animation->addReference();
			}
		}

		inline void addAll(const std::initializer_list<SpriteAnimation*>& animations) {
			for (SpriteAnimation* animation : animations) {
				this->animations.add(animation);
				animation->addReference();
			}
		}

		inline void insert(size_t i, SpriteAnimation* animation) {
			animations.insert(i, animation);
			animation->addReference();
		}

		inline void remove(SpriteAnimation* animation) {
			animations.remove(animation);
			animation->release();
		}

		inline void removeAt(size_t index) {
			auto& animation = animations.get(index);
			animations.removeAt(index);
			animation->release();
		}

		inline void clear() {
			for (auto animation : animations)
				animation->release();
			animations.clear();
		}

		inline ArrayIterator<SpriteAnimation*> begin() {
			return animations.begin();
		}

		inline ConstArrayIterator<SpriteAnimation*> begin() const {
			return animations.begin();
		}

		inline ArrayIterator<SpriteAnimation*> end() {
			return animations.end();
		}

		inline ConstArrayIterator<SpriteAnimation*> end() const {
			return animations.end();
		}

		virtual size_t getSize() const {
			return animations.getSize();
		}

		__declspec(property(get = getSize)) size_t Size;

		inline void set(size_t i, SpriteAnimation* e) {
			SpriteAnimation* animation = animations[i];
			if (animation == e)
				return;
			animation->release();
			animations.set(i, e);
			e->addReference();
		}

		virtual SpriteAnimation* get(size_t i) {
			return animations.get(i);
		}

		/*inline size_t indexOf(const SpriteAnimation* animation) const {
			return animations.indexOf(animation);
		}

		inline bool contains(const SpriteAnimation* animation) const {
			return animations.contains(animation);
		}*/

		inline SpriteAnimation* operator[](size_t i)const {
			return animations[i];
		}

		inline size_t find(const Ghurund::Core::WString& name) {
			return animations.find([&](SpriteAnimation* c) { return c->Name && c->Name->operator==(name); });
		}

		template<class T>
		inline T* find() const {
			return (T*)find(T::GET_TYPE());
		}

		inline size_t find(const Ghurund::Core::Type& type) const {
			return animations.find([&](SpriteAnimation* c) { return c->Type == type; });
		}

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return SpriteAnimationSet::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_LOAD | ResourceFormatOptions::CAN_SAVE);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

		// version 1 used uint32_t durationMs
		static const inline uint32_t VERSION = 2;
#pragma endregion
	};
}
