#pragma once

#include "core/Enum.h"
#include "core/io/DirectoryPath.h"
#include "core/io/FilePath.h"
#include "core/string/String.h"
#include "core/string/StringView.h"
#include "core/string/TextConversionUtils.h"
#include "core/resource/ResourcePath.h"
#include "core/concepts/Concepts.h"

#include <format>

template <>
struct std::formatter<Ghurund::Core::AString, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::AString& s, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::AString, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::AString& s, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(Ghurund::Core::convertText<char, wchar_t>(s).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::WString, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::WString& s, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(Ghurund::Core::convertText<wchar_t, char>(s).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::WString, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::WString& s, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::AStringView, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::AStringView& s, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::AStringView, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::AStringView& s, FormatContext& ctx) const {
        const wchar_t* str = Ghurund::Core::convertText<char, wchar_t>(s.Data);
        auto f = std::formatter<const wchar_t*, wchar_t>::format(str, ctx);
        delete[] str;
        return f;
    }
};

template <>
struct std::formatter<Ghurund::Core::WStringView, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::WStringView& s, FormatContext& ctx) const {
        const char* str = Ghurund::Core::convertText<wchar_t, char>(s.Data);
        auto f = std::formatter<const char*, char>::format(str, ctx);
        delete[] str;
        return f;
    }
};

template <>
struct std::formatter<Ghurund::Core::WStringView, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::WStringView& s, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(s.Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::DirectoryPath, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::DirectoryPath& s, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(Ghurund::Core::convertText<wchar_t, char>(s.toString()).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::DirectoryPath, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::DirectoryPath& s, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(s.toString().Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::FilePath, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::FilePath& s, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(Ghurund::Core::convertText<wchar_t, char>(s.toString()).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::FilePath, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::FilePath& s, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(s.toString().Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::ResourcePath, char>:std::formatter<const char*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::ResourcePath& s, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(Ghurund::Core::convertText<wchar_t, char>(s.toString()).Data, ctx);
    }
};

template <>
struct std::formatter<Ghurund::Core::ResourcePath, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::ResourcePath& s, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(s.toString().Data, ctx);
    }
};

template <class EnumValueType, class EnumType>
struct std::formatter<Ghurund::Core::Enum<EnumValueType, EnumType>, char>:std::formatter<const wchar_t*, char> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::Enum<EnumValueType, EnumType>& e, FormatContext& ctx) const {
        return std::formatter<const char*, char>::format(e.Name.Data, ctx);
    }
};

template <class EnumValueType, class EnumType>
struct std::formatter<Ghurund::Core::Enum<EnumValueType, EnumType>, wchar_t>:std::formatter<const wchar_t*, wchar_t> {
    template <typename FormatContext>
    auto format(const Ghurund::Core::Enum<EnumValueType, EnumType>& e, FormatContext& ctx) const {
        return std::formatter<const wchar_t*, wchar_t>::format(Ghurund::Core::convertText<char, wchar_t>(e.Name).Data, ctx);
    }
};
