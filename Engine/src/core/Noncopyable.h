#pragma once

#pragma warning (disable : 4521)	// multiple copy constructors specified

namespace Ghurund {
    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(Noncopyable&) = delete;
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable& operator=(const Noncopyable&) = delete;
    };
}