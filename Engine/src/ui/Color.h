#pragma once

#include "ui/Graphics2D.h"

#include <stdint.h>

namespace Ghurund::UI {
    class Color {
    private:
        uint32_t value;
        float r, g, b, a;

    public:
        Color(uint32_t value) {
            Value = value;
        }

        Color(float r, float g, float b, float a = 1.0f) {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
            value = (((uint8_t)(a * 255) & 0xff) << 24) | (((uint8_t)(r * 255) & 0xff) << 16) | (((uint8_t)(g * 255) & 0xff) << 8) | ((uint8_t)(b * 255) & 0xff);
        }

        inline float getR() const {
            return r;
        }

        __declspec(property(get = getR)) float R;

        inline float getG() const {
            return g;
        }

        __declspec(property(get = getG)) float G;

        inline float getB() const {
            return b;
        }

        __declspec(property(get = getB)) float B;

        inline float getA() const {
            return a;
        }

        __declspec(property(get = getA)) float A;

        inline uint32_t getValue() const {
            return value;
        }

        inline void setValue(uint32_t value) {
            this->value = value;
            a = ((value >> 24) & 0xff) / 255.f;
            r = ((value >> 16) & 0xff) / 255.f;
            g = ((value >> 8) & 0xff) / 255.f;
            b = (value & 0xff) / 255.f;
        }

        __declspec(property(get = getValue, put = setValue)) uint32_t Value;

        inline D2D_VECTOR_4F getVector() const {
            return { r,g,b,a };
        }

        inline void setVector(const D2D_VECTOR_4F& vector) {
            r = vector.x;
            g = vector.y;
            b = vector.z;
            a = vector.w;
        }

        __declspec(property(get = getVector, put = setVector)) D2D_VECTOR_4F Vector;

        inline Color& operator=(uint32_t v) {
            Value = v;
            return *this;
        }

        inline operator uint32_t() const {
            return value;
        }
    };

    constexpr uint32_t colorWithAlpha(float alpha, uint32_t color) {
        uint32_t a = (uint32_t)(alpha * 0xff);
        return ((a & 0xff) << 24) | (color & 0xffffff);
    }

    constexpr uint32_t lerpColors(uint32_t color, uint32_t color2, float amount) {
        uint32_t a = (uint32_t)(((color >> 24) & 0xff) * (1 - amount) + ((color2 >> 24) & 0xff) * amount);
        uint32_t r = (uint32_t)(((color >> 16) & 0xff) * (1 - amount) + ((color2 >> 16) & 0xff) * amount);
        uint32_t g = (uint32_t)(((color >> 8) & 0xff) * (1 - amount) + ((color2 >> 8) & 0xff) * amount);
        uint32_t b = (uint32_t)((color & 0xff) * (1 - amount) + (color2 & 0xff) * amount);
        return ((a & 0xff) << 24) | ((r & 0xff) << 16) | ((g & 0xff) << 8) | (b & 0xff);
    }
}