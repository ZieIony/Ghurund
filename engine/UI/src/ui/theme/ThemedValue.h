#pragma once

#include "AttributeKey.h"

#include "core/Color.h"

namespace Ghurund::UI {
	class Theme;

	template<typename KeyType, typename ValueType>
	class ThemedValue {
	private:
		KeyType* key = nullptr;
		ValueType value;

	public:
		ThemedValue(const ValueType& value):value(value) {}

		ThemedValue(const KeyType& key):key(ghnew KeyType(key)) {}

		~ThemedValue() {
			delete key;
		}

		inline KeyType* getKey() const {
			return key;
		}

		__declspec(property(get = getKey)) KeyType* Key;

		inline const ValueType& getValue() const {
			return value;
		}

		__declspec(property(get = getValue)) const ValueType& Value;
	};

	template<typename KeyType, Derived<RefCountedObject> ValueType>
	class ThemedValue<KeyType, ValueType> {
	private:
		KeyType* key = nullptr;
		ValueType* value = nullptr;

	public:
		ThemedValue(ValueType* value):value(value) {
			if (value)
				value->addReference();
		}

		ThemedValue(const KeyType& key):key(ghnew KeyType(key)) {}

		~ThemedValue() {
			delete key;
			if (value)
				value->release();
		}

		inline KeyType* getKey() const {
			return key;
		}

		__declspec(property(get = getKey)) KeyType* Key;

		inline ValueType* getValue() const {
			return value;
		}

		__declspec(property(get = getValue)) ValueType* Value;
	};

	using ThemedTexture = ThemedValue<TextureKey, IntrusivePointer<ITexture>>;
	using ThemedColor = ThemedValue<ColorKey, Color>;
	using ThemedTextStyle = ThemedValue<TextStyleKey, IntrusivePointer<TextStyle>>;

	template<typename KeyType, typename ValueType>
	inline ValueType resolveThemeValue(const Theme& theme, const KeyType& key) = delete;

	template<>
	IntrusivePointer<ITexture> resolveThemeValue(const Theme& theme, const TextureKey& key);

	template<>
	Color resolveThemeValue(const Theme& theme, const ColorKey& key);

	template<>
	IntrusivePointer<TextStyle> resolveThemeValue(const Theme& theme, const TextStyleKey& key);
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::ThemedTexture>();

	template<>
	const Type& getType<Ghurund::UI::ThemedColor>();

	template<>
	const Type& getType<Ghurund::UI::ThemedTextStyle>();
}