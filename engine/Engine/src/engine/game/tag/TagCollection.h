#pragma once

#include "Tag.h"

#include "core/collection/Set.h"
#include "core/object/Noncopyable.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class TagCollection:public Noncopyable {
	private:
		Set<Tag> tags;

	public:
		inline void add(const Tag& tag) {
			tags.put(tag);
		}

		inline void remove(const Tag& tag) {
			tags.remove(tag);
		}

		inline bool contains(const Tag& tag) const {
			return tags.contains(tag);
		}

		inline bool containsAll(const TagCollection& other) const {
			for (auto& tag : other.tags) {
				if (!contains(tag))
					return false;
			}
			return true;
		}

		inline bool containsAny(const TagCollection& other) const {
			for (auto& tag : other.tags) {
				if (contains(tag))
					return true;
			}
			return false;
		}

		inline bool containsNone(const TagCollection& other) const {
			for (auto& tag : other.tags) {
				if (contains(tag))
					return false;
			}
			return true;
		}

		inline bool matches(const Tag& tag) const {
			for (auto& t : tags) {
				if (t.matches(tag))
					return true;
			}
			return false;
		}

		inline bool matchesAll(const TagCollection& other) const {
			for (auto& tag : other.tags) {
				if (!matches(tag))
					return false;
			}
			return true;
		}

		inline bool matchesAny(const TagCollection& other) const {
			for (auto& tag : other.tags) {
				if (matches(tag))
					return true;
			}
			return false;
		}

		inline bool matchesNone(const TagCollection& other) const {
			for (auto& tag : other.tags) {
				if (matches(tag))
					return false;
			}
			return true;
		}

		inline size_t getTagCount() const {
			return tags.Size;
		}

		__declspec(property(get = getTagCount)) size_t TagCount;
	};
}
