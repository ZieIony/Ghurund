#pragma once

#include "core/math/MathUtils.h"
#include "core/reflection/Type.h"

#include <stdint.h>
#include <DirectXMath.h>

namespace Ghurund::Core {

	class Color {
	private:
		uint32_t value;
		float r, g, b, a;

	public:
		Color() {
			Value = 0;
		};

		Color(uint32_t value) {
			Value = value;
		}

		Color(uint8_t r, uint8_t g, uint8_t b) {
			this->r = r / 255.0f;
			this->g = g / 255.0f;
			this->b = b / 255.0f;
			this->a = 1.0f;
			value = 0xff000000 | (r << 16) | (g << 8) | b;
		}

		Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b) {
			this->r = r / 255.0f;
			this->g = g / 255.0f;
			this->b = b / 255.0f;
			this->a = a / 255.0f;
			value = (a << 24) | (r << 16) | (g << 8) | b;
		}

		Color(float r, float g, float b) {
			this->r = std::max(0.0f, std::min(r, 1.0f));
			this->g = std::max(0.0f, std::min(g, 1.0f));
			this->b = std::max(0.0f, std::min(b, 1.0f));
			this->a = 1.0f;
			value = 0xff000000 | (((uint8_t)(r * 255) & 0xff) << 16) | (((uint8_t)(g * 255) & 0xff) << 8) | ((uint8_t)(b * 255) & 0xff);
		}

		Color(float a, float r, float g, float b) {
			this->r = std::max(0.0f, std::min(r, 1.0f));
			this->g = std::max(0.0f, std::min(g, 1.0f));
			this->b = std::max(0.0f, std::min(b, 1.0f));
			this->a = std::max(0.0f, std::min(a, 1.0f));
			value = (((uint8_t)(a * 255) & 0xff) << 24) | (((uint8_t)(r * 255) & 0xff) << 16) | (((uint8_t)(g * 255) & 0xff) << 8) | ((uint8_t)(b * 255) & 0xff);
		}

		inline float getR() const {
			return r;
		}

		inline void setR(float r) {
			this->r = std::max(0.0f, std::min(r, 1.0f));
			value = ((uint32_t)(this->r * 255) << 16) | (value & 0xff00ffff);
		}

		__declspec(property(get = getR, put = setR)) float R;

		inline float getG() const {
			return g;
		}

		inline void setG(float g) {
			this->g = std::max(0.0f, std::min(g, 1.0f));
			value = ((uint32_t)(this->g * 255) << 8) | (value & 0xffff00ff);
		}

		__declspec(property(get = getG, put = setG)) float G;

		inline float getB() const {
			return b;
		}

		inline void setB(float b) {
			this->b = std::max(0.0f, std::min(b, 1.0f));
			value = (uint32_t)(this->b * 255) | (value & 0xffffff00);
		}

		__declspec(property(get = getB, put = setB)) float B;

		inline float getA() const {
			return a;
		}

		inline void setA(float a) {
			this->a = std::max(0.0f, std::min(a, 1.0f));
			value = ((uint32_t)(this->a * 255) << 24) | (value & 0xffffff);
		}

		__declspec(property(get = getA, put = setA)) float A;

		inline uint32_t getValue() const {
			return value;
		}

		inline void setValue(uint32_t value) {
			this->value = value;
			a = ((value >> 24) & 0xff) / 255.0f;
			r = ((value >> 16) & 0xff) / 255.0f;
			g = ((value >> 8) & 0xff) / 255.0f;
			b = (value & 0xff) / 255.0f;
		}

		__declspec(property(get = getValue, put = setValue)) uint32_t Value;

		inline Color& operator=(uint32_t v) {
			Value = v;
			return *this;
		}

		inline operator uint32_t() const {
			return value;
		}

		inline ::DirectX::XMFLOAT4 toVector() const {
			return { r, g, b, a };
		}

		inline Color toLinear() const {
			return {
				a,
				r < 0.04045f ? r / 12.92f : powf((r + 0.055f) / 1.055f, 2.4f),
				g < 0.04045f ? g / 12.92f : powf((g + 0.055f) / 1.055f, 2.4f),
				b < 0.04045f ? b / 12.92f : powf((b + 0.055f) / 1.055f, 2.4f)
			};
		}

		inline Color toSRGB() const {
			return {
				a,
				r < 0.0031308 ? 12.92f * r : 1.055f * powf(abs(r), 1.0f / 2.4f) - 0.055f,
				g < 0.0031308 ? 12.92f * g : 1.055f * powf(abs(g), 1.0f / 2.4f) - 0.055f,
				b < 0.0031308 ? 12.92f * b : 1.055f * powf(abs(b), 1.0f / 2.4f) - 0.055f
			};
		}

		// use linear color space
		inline float getBrightness() const {
			return 0.213f * r + 0.715f * g + 0.072f * b;
		}

		__declspec(property(get = getBrightness)) float Brightness;

		static Color parse(const AString& color);

		String toString() const;
	};

	constexpr inline uint32_t colorWithAlpha(float alpha, uint32_t color) {
		uint32_t a = (uint32_t)(alpha * 0xff);
		return ((a & 0xff) << 24) | (color & 0xffffff);
	}

	constexpr inline uint32_t lerpColors(uint32_t color, uint32_t color2, float amount) {
		uint32_t a = (uint32_t)(((color >> 24) & 0xff) * (1 - amount) + ((color2 >> 24) & 0xff) * amount);
		uint32_t r = (uint32_t)(((color >> 16) & 0xff) * (1 - amount) + ((color2 >> 16) & 0xff) * amount);
		uint32_t g = (uint32_t)(((color >> 8) & 0xff) * (1 - amount) + ((color2 >> 8) & 0xff) * amount);
		uint32_t b = (uint32_t)((color & 0xff) * (1 - amount) + (color2 & 0xff) * amount);
		return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
	}

	template<>
	const Type& getType<Color>();

	template<>
	inline Color lerp(Color val1, Color val2, float fact) {
		return Color(lerpColors(val1, val2, fact));
	}
}
