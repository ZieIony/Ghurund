#pragma once

#include "Tree.h"

namespace Ghurund::Core {
	template<typename Key, typename Value>
	struct KeyValuePair {
		Key key;
		Value value;

		inline bool operator==(const KeyValuePair& other) const {
			return key == other.key && value == other.value;
		}
	};

	template<typename Key, typename Value>
	struct MapTraits {
		using key_t = Key;
		using value_t = Value;
		using data_t = KeyValuePair<key_t, value_t>;

		inline const key_t& getKey(const data_t& data) const {
			return data.key;
		}

		inline data_t makeData(const key_t& key, const value_t& value = {}) const {
			return { key, value };
		}
	};

	template<typename Key, typename Value, typename AllocatorType = SimpleAllocator, typename Traits = MapTraits<Key, Value>>
	class Map:public Tree<Traits, AllocatorType> {
	private:
		using super_t = Tree<Traits, AllocatorType>;

	public:
		explicit Map(const AllocatorType& a = AllocatorType()):super_t(a) {}

		Map(const Map& other):super_t(other) {}

		template<Iterable<data_t> CollectionType>
		Map(const CollectionType& collection):super_t(collection) {}

		Map(const std::initializer_list<typename MapTraits<Key, Value>::data_t>& list):super_t() {
			__super::putAll(list);
		}

		Map(Map&& other):super_t(std::move(other)) {}

		inline void put(const Key& key, const Value& value) {
			__super::put(key, value);
		}

		Map& operator=(const Map& other) {
			__super::operator=(other);
			return *this;
		}

		Map& operator=(Map&& other) {
			__super::operator=(std::move(other));
			return *this;
		}

#ifdef _DEBUG
		inline bool containsValue(const Value& value) const {
			for (auto& [k, v] : *this)
				if (v == value)
					return true;
			return false;
		}
#endif
	};
}