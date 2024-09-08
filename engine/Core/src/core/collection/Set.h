#pragma once

#include "Tree.h"

namespace Ghurund::Core {
	template<typename Key>
	struct SetTraits {
		using key_t = Key;
		using value_t = Key;
		using data_t = Key;

		inline const Key& getKey(const data_t& data) const {
			return data;
		}

		inline data_t makeData(const Key& key) const {
			return key;
		}
	};

	/**
	 * Keeps order, cannot have duplicates
	 */
	template<typename Key, typename AllocatorType = SimpleAllocator, typename Traits = SetTraits<Key>>
	class Set:public Tree<Traits, AllocatorType> {
	private:
		using super_t = Tree<Traits, AllocatorType>;

	public:
		explicit Set(const AllocatorType& a = AllocatorType()):super_t(a) {}

		Set(const Set& other):super_t(other) {}

		template<Iterable<Key> CollectionType>
		Set(const CollectionType& collection):super_t(collection) {}

		Set(const std::initializer_list<Key>& list):super_t() {
			__super::putAll(list);
		}

		Set(Set&& other):super_t(std::move(other)) {}

		inline void put(const Key& key) {
			__super::put(key);
		}

		Set& operator=(const Set& other) {
			__super::operator=(other);
			return *this;
		}

		Set& operator=(Set&& other) noexcept {
			__super::operator=(std::move(other));
			return *this;
		}
	};
}