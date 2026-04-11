#pragma once

#include "core/string/String.h"

#include <dbghelp.h>

namespace Ghurund::Core {
    struct StackTraceEntry {
        uint64_t address = 0;
        AString name;
        WString fileName;
        uint32_t fileLine = 0;

        StackTraceEntry() {}

        StackTraceEntry(
            const StackTraceEntry& other
        ):address(other.address), name(other.name), fileName(other.fileName), fileLine(other.fileLine) {}

        StackTraceEntry(
            StackTraceEntry&& other
        ) noexcept:
            address(std::move(other.address)),
            name(std::move(other.name)),
            fileName(std::move(other.fileName)),
            fileLine(std::move(other.fileLine)) {
        }
    };

    class StackTrace {
    private:
        static const inline uint16_t MAX_FRAMES_TO_CAPTURE = 64;

        HANDLE process;
        void* stack[MAX_FRAMES_TO_CAPTURE];
        uint16_t numberOfFrames;
        _SYMBOL_INFO* symbol;

    public:
        StackTrace(HANDLE process);

        ~StackTrace() {
            delete[](uint8_t*)symbol;
        }

        inline uint16_t getSize() const {
            return numberOfFrames;
        }

        __declspec(property(get = getSize)) uint16_t Size;

        StackTraceEntry get(uint16_t index) const;

        inline StackTraceEntry operator[](uint16_t index) const {
            return get(index);
        }
    };
}
