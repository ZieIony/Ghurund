#pragma once

#include "core/io/DirectoryPath.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"

#include <fmt/format.h>

template <>
struct fmt::formatter<Ghurund::ASCIIString> {
    template <typename FormatContext>
    auto format(const Ghurund::ASCIIString& s, FormatContext& ctx) {
        return format_to(
            ctx.out(),
            "{s}",
            Ghurund::String(s).getData());
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};

template <>
struct fmt::formatter<Ghurund::UnicodeString> {
    template <typename FormatContext>
    auto format(const Ghurund::UnicodeString& s, FormatContext& ctx) {
        return format_to(
            ctx.out(),
            "{s}",
            Ghurund::String(s).getData());
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
        return format_to(
            ctx.out(),
            "{s}",
            Ghurund::String(s.get()).getData());
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
        return format_to(
            ctx.out(),
            "{s}",
            Ghurund::String(s.get()).getData());
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
        return format_to(
            ctx.out(),
            "{s}",
            e.Name);
    }

    constexpr auto parse(format_parse_context& ctx) {
        auto it = ctx.begin(), end = ctx.end();
        if (it != end && *it != '}')
            throw format_error("invalid format");
        return it;
    }
};
