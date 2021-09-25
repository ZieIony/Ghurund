#pragma once

namespace Ghurund::Core {
    class CriticalSection {
    private:
        CRITICAL_SECTION section;

    public:
        CriticalSection() {
            InitializeCriticalSection(&section);
        }

        CriticalSection(CriticalSection &other) = delete;

        ~CriticalSection() {
            DeleteCriticalSection(&section);
        }

        inline void enter() {
            EnterCriticalSection(&section);
        }

        inline bool tryEnter() {
            return TryEnterCriticalSection(&section);
        }

        inline void leave() {
            LeaveCriticalSection(&section);
        }

        inline CRITICAL_SECTION* operator&() {
            return &section;
        }
    };

    class SectionLock {
    private:
        CriticalSection& section;

    public:
        SectionLock(CriticalSection& section):section(section) {
            section.enter();
        }

        ~SectionLock() {
            section.leave();
        }
    };
}