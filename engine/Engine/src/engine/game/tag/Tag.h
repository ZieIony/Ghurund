#pragma once

#include "core/object/NotNull.h"
#include "core/string/String.h"
#include "core/collection/Map.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	struct TagData {
		AString name;
		TagData* parent;
		Map<AString, TagData*> children;

		TagData(AString name, TagData* parent):name(name), parent(parent) {}
	};

	class Tag {
	private:
		TagData* data;

	public:
		Tag(NotNull<TagData> data):data(data.get()) {}

		Tag(const Tag& other):data(other.data) {}

		Tag(Tag&& other) noexcept:data(std::move(other.data)) {}

		inline const AString& getName() const {
			return data->name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline bool getHasParent() const {
			return data->parent;
		}

		__declspec(property(get = getHasParent)) bool HasParent;

		inline Tag getParent() const {
			return Tag(data->parent);
		}

		__declspec(property(get = getParent)) Tag Parent;

		inline size_t getChildCount() const {
			return data->children.Size;
		}

		__declspec(property(get = getChildCount)) size_t ChildCount;

		inline bool matches(const Tag& other) const {
			auto dataToCompare = other.data;
			while (dataToCompare) {
				if (dataToCompare == data)
					return true;
				dataToCompare = dataToCompare->parent;
			}
			return false;
		}

		inline Tag& operator=(const Tag& other) {
			data = other.data;
			return *this;
		}

		inline Tag& operator=(Tag&& other) noexcept {
			if (this == &other)
				return *this;

			data = std::move(other.data);
			return *this;
		}

		inline constexpr std::strong_ordering operator<=>(const Tag& other) const noexcept {
			return data <=> other.data;
		}

		inline constexpr bool operator==(const Tag& other) const {
			return data == other.data;
		}
	};
}
