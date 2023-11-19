#pragma once

namespace Ghurund::UI {
	class Theme;

	template<typename AttrType, typename ValueType>
	class AttrProperty {
	private:
		AttrType* attr;
		const ValueType* value = nullptr;

	public:
		AttrProperty(const AttrType& attr) :attr((AttrType*)attr.clone()) {}

		AttrProperty(const AttrProperty& other):attr((AttrType*)other.attr->clone()), value(other.value) {}

		~AttrProperty() {
			delete attr;
		}

		inline void resolve(const Theme& theme) {
			value = attr->resolve(theme);
		}

		inline void set(const AttrType& attr) {
			delete this->attr;
			this->attr = (AttrType*)attr.clone();
		}

		inline const ValueType* get() const {
			return value;
		}

		inline bool operator==(const AttrProperty& other) const {
			return ((!attr && !other.attr) || (attr && other.attr && *attr == *other.attr)) &&
				((!value && !other.value) || (value && other.value && *value == *other.value));
		}
	};

	template<typename AttrType, typename ValueType>
	class NullableAttrProperty {
	private:
		AttrType* attr = nullptr;
		const ValueType* value = nullptr;

		NullableAttrProperty(const NullableAttrProperty& other) = delete;
		NullableAttrProperty(NullableAttrProperty&& other) = delete;

	public:
		NullableAttrProperty() {}

		NullableAttrProperty(std::unique_ptr<AttrType> attr) :attr(attr.release()) {}

		~NullableAttrProperty() {
			delete attr;
		}

		inline void resolve(const Theme& theme) {
			if (attr) {
				value = attr->resolve(theme);
			} else {
				value = nullptr;
			}
		}

		inline void set(std::unique_ptr<AttrType> attr) {
			delete this->attr;
			if (attr)
				this->attr = attr.release();
		}

		inline const ValueType* get() const {
			return value;
		}

		inline const bool operator==(const AttrType* attr) const {
			return this->attr == attr;
		}

		inline bool operator==(const NullableAttrProperty& other) const {
			return ((!attr && !other.attr) || (attr && other.attr && *attr == *other.attr)) &&
				((!value && !other.value) || (value && other.value && *value == *other.value));
		}
	};

}