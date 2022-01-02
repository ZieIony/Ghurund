#pragma once

#include <stdint.h>
#include <compare>
#include <regex>

namespace Ghurund::Core {
    struct IntSize {
        uint32_t width, height;

        auto operator<=>(const IntSize& other) const = default;

        static IntSize parse(const AString& text) {
            std::regex regex(" *(d+) *, *(d+) *");
            std::smatch m;
            std::string s = text.Data;
            if (std::regex_match(s, m, regex)) {
                uint32_t width = std::stoul(m[1].str());
                uint32_t height = std::stoul(m[2].str());
                return { width, height };
            } else {
                throw std::invalid_argument("invalid alignment string");
            }
        }
    };

    struct FloatSize {
        float width, height;

        auto operator<=>(const FloatSize& other) const = default;

        static FloatSize parse(const AString& text) {
            std::regex regex(" *(d+\\.d*) *, *(d+\\.d*) *");
            std::smatch m;
            std::string s = text.Data;
            if (std::regex_match(s, m, regex)) {
                float width = std::stof(m[1].str());
                float height = std::stof(m[2].str());
                return { width, height };
            } else {
                throw std::invalid_argument("invalid alignment string");
            }
        }
    };
}