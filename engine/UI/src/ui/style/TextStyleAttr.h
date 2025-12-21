#pragma once

#include "core/object/Object.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	class TextStyleAttr: public Ghurund::Core::Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextStyleAttr::GET_TYPE();
#pragma endregion

	public:
		virtual IntrusivePointer<Ghurund::UI::TextStyle> resolve(const Theme& theme) const = 0;
	};

	class TextStyleValue: public TextStyleAttr {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextStyleValue::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Ghurund::UI::TextStyle> font;

	public:
		TextStyleValue(Ghurund::UI::TextStyle* TextStyle):font(TextStyle) {
			if (font != nullptr)
				font->addReference();
		}

		TextStyleValue& operator=(const TextStyleValue& other) {
			font = other.font;
			return *this;
		}

		TextStyleValue& operator=(TextStyleValue&& other) noexcept {
			if (this == &other)
				return *this;
			font = std::move(other.font);
			return *this;
		}

		virtual IntrusivePointer<Ghurund::UI::TextStyle> resolve(const Theme& theme) const override {
			return font;
		}

		virtual TextStyleValue* clone() const override {
			return ghnew TextStyleValue(font.get());
		}
	};

	class TextStyleRef: public TextStyleAttr {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextStyleRef::GET_TYPE();
#pragma endregion

	private:
		TextStyleKey key;

	public:
		TextStyleRef(TextStyleKey key):key(key) {}

		virtual IntrusivePointer<Ghurund::UI::TextStyle> resolve(const Theme& theme) const override;

		virtual TextStyleRef* clone() const override {
			return ghnew TextStyleRef(key);
		}
	};
}
