#pragma once

namespace Ghurund::Core {
    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(const Noncopyable&) = delete;

        virtual ~Noncopyable() = 0 {};

		Noncopyable& operator=(const Noncopyable&) = delete;
    };
}
