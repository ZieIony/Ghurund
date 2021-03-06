#pragma once

namespace Ghurund {
    class CriticalSection {
    private:
        CRITICAL_SECTION section;

    public:
        CriticalSection() {
            InitializeCriticalSection(&section);
        }

        CriticalSection(CriticalSection &cs) = delete;

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
    };
}