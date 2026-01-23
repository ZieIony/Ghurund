#pragma once

#include "ThemedValue.h"

namespace Ghurund::UI {
	class Theme;

	template<typename KeyType, typename ValueType>
	class ThemedValueProperty {
	private:
		KeyType* key = nullptr;
		ValueType value = {};

	public:
		ThemedValueProperty() {}

		ThemedValueProperty(
			const ThemedValue<KeyType, ValueType>& ValueType
		):value(ValueType.Value), key(ValueType.Key ? ghnew KeyType(*ValueType.Key) : nullptr) {
		}

		ThemedValueProperty(const ValueType& value):value(value) {}

		ThemedValueProperty(const KeyType& key):key(ghnew KeyType(key)) {}

		~ThemedValueProperty() {
			delete key;
		}

		inline void resolve(const Theme& theme) {
			if (key)
				value = resolveThemeValue<KeyType, ValueType>(theme, *key);
		}

		inline void set(const ValueType& value) {
			this->value = value;
			delete key;
			key = nullptr;
		}

		inline void set(const KeyType& key) {
			delete this->key;
			this->key = ghnew KeyType(key);
		}

		inline const ValueType& get() const {
			return value;
		}
	};

	template<typename KeyType, Derived<RefCountedObject> ValueType>
	class ThemedValueProperty<KeyType, ValueType> {
	private:
		KeyType* key = nullptr;
		ValueType* value = nullptr;

	public:
		ThemedValueProperty() {}

		ThemedValueProperty(
			const ThemedValue<KeyType, ValueType>& ValueType
		):value(ValueType.Value), key(ValueType.Key ? ghnew KeyType(*ValueType.Key) : nullptr) {
			if (value)
				value->addReference();
		}

		ThemedValueProperty(ValueType* value):value(value) {
			if (value)
				value->addReference();
		}

		ThemedValueProperty(const KeyType& key):key(ghnew KeyType(key)) {}

		~ThemedValueProperty() {
			delete key;
			if (value)
				value->release();
		}

		inline void resolve(const Theme& theme) {
			if (key) {
				ValueType* v = resolveThemeValue<KeyType, ValueType*>(theme, *key);
				setPointer(value, v);
				if (v)
					v->release();
			}
		}

		inline void set(ValueType* value) {
			setPointer(this->value, value);
			delete key;
			key = nullptr;
		}

		inline void set(const KeyType& key) {
			delete this->key;
			this->key = ghnew KeyType(key);
			if (value) {
				value->release();
				value = nullptr;
			}
		}

		inline ValueType* get() const {
			return value;
		}

		inline ValueType* operator->() {
			return value;
		}

		inline bool operator==(ValueType* value) const {
			return this->value == value;
		}
	};

	template<typename KeyType, typename ValueType>
	class ThemedValueProperty<KeyType, ValueType*> {
	private:
		KeyType* key = nullptr;
		ValueType* value = nullptr;

	public:
		ThemedValueProperty():value(nullptr), key(nullptr) {}

		ThemedValueProperty(
			const ThemedValue<KeyType, ValueType>& value
		):value(ghnew ValueType(value.value)), key(value.key ? ghnew KeyType(*value.key) : nullptr) {
		}

		ThemedValueProperty(const ValueType& value):value(ghnew ValueType(value)) {}

		ThemedValueProperty(const KeyType& key):key(ghnew KeyType(key)) {}

		~ThemedValueProperty() {
			delete key;
		}

		inline void resolve(const Theme& theme) {
			if (key)
				value = ghnew ValueType(resolveThemeValue(theme, *key));
		}

		inline void set(nullptr_t) {
			delete this->value;
			value = nullptr;
			delete key;
			key = nullptr;
		}

		inline void set(const ValueType& value) {
			delete this->value;
			this->value = ghnew ValueType(value);
			delete key;
			key = nullptr;
		}

		inline void set(const KeyType& key) {
			delete value;
			value = nullptr;
			delete this->key;
			this->key = ghnew KeyType(key);
		}

		inline const ValueType* get() const {
			return value;
		}
	};

}