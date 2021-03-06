#pragma once

#include "core/Enum.h"
#include "core/io/DirectoryPath.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"
#include "core/string/StringView.h"
#include "core/string/TextConversionUtils.h"

template <>
struct fmt::formatter<Ghurund::AString> {
    template <typename FormatContext>
    auto format(const Ghurund::AString& s, FormatContext& ctx) {
        Ghurund::String str = Ghurund::toTchar(s.Data);
        return format_to(ctx.out(), "{s}", str.Data);
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <>
struct fmt::formatter<Ghurund::WString> {
    template <typename FormatContext>
    auto format(const Ghurund::WString& s, FormatContext& ctx) {
        const tchar* str = Ghurund::toTchar(s.Data);
        auto f = format_to(ctx.out(), "{s}", str);
        delete[] str;
        return f;
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <>
struct fmt::formatter<Ghurund::AStringView> {
    template <typename FormatContext>
    auto format(const Ghurund::AStringView& s, FormatContext& ctx) {
        const char* str = Ghurund::toTchar(s.Data);
        auto f = format_to(ctx.out(), "{s}", str);
        delete[] str;
        return f;
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <>
struct fmt::formatter<Ghurund::WStringView> {
    template <typename FormatContext>
    auto format(const Ghurund::WStringView& s, FormatContext& ctx) {
        const tchar* str = Ghurund::toTchar(s.Data);
        auto f = format_to(ctx.out(), "{s}", str);
        delete[] str;
        return f;
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <>
struct fmt::formatter<Ghurund::DirectoryPath> {
    template <typename FormatContext>
    auto format(const Ghurund::DirectoryPath& s, FormatContext& ctx) {
        const tchar* str = Ghurund::toTchar(s.toString().Data);
        auto f = format_to(ctx.out(), "{s}", str);
        delete[] str;
        return f;
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <>
struct fmt::formatter<Ghurund::FilePath> {
    template <typename FormatContext>
    auto format(const Ghurund::FilePath& s, FormatContext& ctx) {
        const tchar* str = Ghurund::toTchar(s.toString().Data);
        auto f = format_to(ctx.out(), "{s}", str);
        delete[] str;
        return f;
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <class EnumValueType, class EnumType>
struct fmt::formatter<Ghurund::Enum<EnumValueType, EnumType>> {
    template <typename FormatContext>
    auto format(const Ghurund::Enum<EnumValueType, EnumType>& e, FormatContext& ctx) {
        return format_to(ctx.out(), "{s}", e.Name);
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};
