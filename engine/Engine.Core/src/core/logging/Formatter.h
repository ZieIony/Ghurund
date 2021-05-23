#pragma once

#include "core/Enum.h"
#include "core/io/DirectoryPath.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"
#include "core/string/StringView.h"
#include "core/string/TextConversionUtils.h"

#include <format>

template <>
struct std::formatter<Ghurund::AString, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::AString& s, FormatContext& ctx) {
        return std::formatter<const char*, char>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::AString, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::AString& s, FormatContext& ctx) {
        return std::formatter<const wchar_t*, wchar_t>::format(Ghurund::convertText<char, wchar_t>(s).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::WString, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::WString& s, FormatContext& ctx) {
        return std::formatter<const char*, char>::format(Ghurund::convertText<wchar_t, char>(s).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::WString, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::WString& s, FormatContext& ctx) {
        return std::formatter<const wchar_t*, wchar_t>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::AStringView, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::AStringView& s, FormatContext& ctx) {
        return std::formatter<const char*, char>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::AStringView, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::AStringView& s, FormatContext& ctx) {
        const wchar_t* str = Ghurund::convertText<char, wchar_t>(s.Data);
        auto f = std::formatter<const wchar_t*, wchar_t>::format(str, ctx);
        delete[] str;
        return f;
    }
};

template <>
struct std::formatter<Ghurund::WStringView, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::WStringView& s, FormatContext& ctx) {
        const char* str = Ghurund::convertText<wchar_t, char>(s.Data);
        auto f = std::formatter<const char*, char>::format(str, ctx);
        delete[] str;
        return f;
    }
};

template <>
struct std::formatter<Ghurund::WStringView, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::WStringView& s, FormatContext& ctx) {
        return std::formatter<const wchar_t*, wchar_t>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::DirectoryPath, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::DirectoryPath& s, FormatContext& ctx) {
        return std::formatter<const char*, char>::format(Ghurund::convertText<wchar_t, char>(s.toString()).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::DirectoryPath, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::DirectoryPath& s, FormatContext& ctx) {
        return std::formatter<const wchar_t*, wchar_t>::format(s.toString().Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::FilePath, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::FilePath& s, FormatContext& ctx) {
        return std::formatter<const char*, char>::format(Ghurund::convertText<wchar_t, char>(s.toString()).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::FilePath, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::FilePath& s, FormatContext& ctx) {
        return std::formatter<const wchar_t*, wchar_t>::format(s.toString().Data, ctx);
    }
};

template <class EnumValueType, class EnumType>
struct std::formatter<Ghurund::Enum<EnumValueType, EnumType>, char>:std::formatter<const wchar_t*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Enum<EnumValueType, EnumType>& e, FormatContext& ctx) {
        return std::formatter<const char*, char>::format(e.Name.Data, ctx);
    }
};

template <class EnumValueType, class EnumType>
struct std::formatter<Ghurund::Enum<EnumValueType, EnumType>, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Enum<EnumValueType, EnumType>& e, FormatContext& ctx) {
        return std::formatter<const wchar_t*, wchar_t>::format(Ghurund::convertText<char, wchar_t>(e.Name).Data, ctx);
    }
};
