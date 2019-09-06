#pragma once

namespace Ghurund {
    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(const Noncopyable&) = delete;

		virtual ~Noncopyable() = default;

		Noncopyable& operator=(const Noncopyable&) = delete;
    };
}