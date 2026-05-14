#pragma once

#include "Tag.h"

#include <core/string/String.h>
#include "core/collection/Map.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class TagManager {
	private:
		Map<AString, TagData*> tags;

		void removeTag(TagData* tag);

	public:
		~TagManager() {
			for (auto& tag : tags)
				delete tag.value;
		}

		void registerTag(const AString& name);

		void unregisterTag(const AString& name);

		bool containsTag(const AString& name) {
			return tags.contains(name);
		}

		inline Tag getTag(const AString& name) const {
			return Tag(tags[name]);
		}

		inline void unregisterAllTags() {
			tags.clear();
		}

		inline size_t getTagCount() const {
			return tags.Size;
		}

		__declspec(property(get = getTagCount)) size_t TagCount;
	};
}
