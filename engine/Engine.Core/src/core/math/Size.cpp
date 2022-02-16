#include "ghcpch.h"
#include "Size.h"

namespace Ghurund::Core {
    IntSize IntSize::parse(const AString& text) {
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

    template<>
    String toString(const IntSize& obj) {
        return std::format(_T("[{}, {}]"), obj.width, obj.height).c_str();
    }

    FloatSize FloatSize::parse(const AString& text) {
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

    template<>
    String toString(const FloatSize& obj) {
        return std::format(_T("[{}, {}]"), obj.width, obj.height).c_str();
    }
}