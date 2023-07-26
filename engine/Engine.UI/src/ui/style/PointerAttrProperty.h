#pragma once

namespace Ghurund::UI {
	class Theme;

	template<typename AttrType, typename ValueType>
	class PointerAttrProperty {
	private:
		AttrType* attr = nullptr;
		ValueType* value = nullptr;

		PointerAttrProperty(const PointerAttrProperty& other) = delete;
		PointerAttrProperty(PointerAttrProperty&& other) = delete;

	public:
		PointerAttrProperty() {}

		PointerAttrProperty(std::unique_ptr<AttrType> attr):attr(attr.release()) {}

		~PointerAttrProperty() {
			delete attr;
			if (value)
				value->release();
		}

		inline void resolve(const Theme& theme) {
			if (attr)
				setPointer(value, attr->resolve(theme));
		}

		inline void set(std::unique_ptr<AttrType> attr) {
			delete this->attr;
			safeRelease(value);
			if (attr)
				this->attr = attr.release();
		}

		inline ValueType* get() const {
			return value;
		}

		inline const bool operator==(const AttrType* attr) const {
			return this->attr == attr;
		}
	};

}