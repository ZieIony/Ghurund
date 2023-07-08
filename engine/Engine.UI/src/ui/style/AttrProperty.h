#pragma once

namespace Ghurund::UI {
	class Theme;

	template<typename AttrType, typename ValueType>
	class AttrProperty {
	private:
		AttrType* attr;
		const ValueType* value = nullptr;

		AttrProperty(const AttrProperty& other) = delete;
		AttrProperty(AttrProperty&& other) = delete;

	public:
		AttrProperty(const AttrType& attr) :attr((AttrType*)attr.clone()) {}

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
			if (attr)
				value = attr->resolve(theme);
		}

		inline void set(std::unique_ptr<AttrType> attr) {
			delete this->attr;
			if (attr)
				this->attr = attr.release();
		}

		inline const ValueType* get() const {
			return value;
		}
	};

}