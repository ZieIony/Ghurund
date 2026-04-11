#include "ghcpch.h"

namespace Ghurund::Core {
    StackTrace::StackTrace(HANDLE process):process(process) {
        numberOfFrames = CaptureStackBackTrace(1, MAX_FRAMES_TO_CAPTURE, stack, nullptr);

        constexpr int symbolStructSize = sizeof(SYMBOL_INFO) + MAX_SYM_NAME * sizeof(TCHAR);
        symbol = (SYMBOL_INFO*)(ghnew uint8_t[symbolStructSize]);
        symbol->SizeOfStruct = sizeof(SYMBOL_INFO);
        symbol->MaxNameLen = MAX_SYM_NAME;
    }

    StackTraceEntry StackTrace::get(uint16_t index) const {
        DWORD64 address = (DWORD64)stack[index];
        StackTraceEntry entry;

        DWORD64 displacement = 0;
        if (SymFromAddr(process, address, &displacement, symbol)) {
            entry.address = symbol->Address;
            entry.name = AString(symbol->Name, symbol->NameLen);
        } else {
            DWORD error = GetLastError();
        }

        DWORD displacement2 = 0;
        IMAGEHLP_LINEW64 line = {};  // IMAGEHLP_LINEW uses char instead of wchar_t
        line.SizeOfStruct = sizeof(IMAGEHLP_LINEW64);
        if (SymGetLineFromAddrW64(process, address, &displacement2, &line)) {
            entry.fileName = line.FileName;
            entry.fileLine = line.LineNumber;
        } else {
            DWORD error = GetLastError();
        }

        return entry;
    }
}
