#pragma once

namespace Ghurund::Core {
    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(const Noncopyable&) = delete;

		virtual ~Noncopyable() = default;

		Noncopyable& operator=(const Noncopyable&) = delete;
    };
}