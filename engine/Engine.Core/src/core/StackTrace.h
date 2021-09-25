#pragma once

#include "core/string/String.h"

#include <dbghelp.h>

namespace Ghurund::Core {
    class StackTrace {
    private:
        static const inline uint16_t MAX_FRAMES_TO_CAPTURE = 64;

        HANDLE process;
        void* stack[MAX_FRAMES_TO_CAPTURE];
        uint16_t numberOfFrames;
        _SYMBOL_INFO* symbol;

    public:
        struct Entry {
            uint64_t address = 0;
            AString name;
            WString fileName;
            uint32_t fileLine = 0;
        };

        StackTrace(HANDLE process):process(process) {
            numberOfFrames = CaptureStackBackTrace(1, MAX_FRAMES_TO_CAPTURE, stack, nullptr);

            constexpr int symbolStructSize = sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(char);
            symbol = (SYMBOL_INFO*)(ghnew uint8_t[symbolStructSize]);
            symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
            symbol->MaxNameLen = MAX_SYM_NAME;
        }

        ~StackTrace() {
            delete[](uint8_t*)symbol;
        }

        inline uint16_t getSize() const {
            return numberOfFrames;
        }

        __declspec(property(get = getSize)) uint16_t Size;

        inline Entry get(uint16_t index) const {
            DWORD64 address = (DWORD64)stack[index];
            Entry entry;

            DWORD64 displacement = 0;
            if (SymFromAddr(process, address, &displacement, symbol)) {
                entry.address = symbol->Address;
                entry.name = AString(symbol->Name, symbol->NameLen);
            }

            DWORD displacement2 = 0;
            IMAGEHLP_LINEW64 line;  // IMAGEHLP_LINEW uses char instead of wchar_t
            line.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);
            if (SymGetLineFromAddrW64(process, address, &displacement2, &line)) {
                entry.fileName = line.FileName;
                entry.fileLine = line.LineNumber;
            }

            return entry;
        }

        inline Entry operator[](uint16_t index) const {
            return get(index);
        }
    };
}