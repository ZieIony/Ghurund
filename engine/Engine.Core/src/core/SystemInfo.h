#pragma once

#include "Common.h"
#include <cstdint>
#include <Windows.h>
#include <psapi.h>

namespace Ghurund {
    class SystemInfo {
    private:
        SystemInfo() = delete;

        template<typename Type>
        static uint8_t countSetBits(Type n) {
            unsigned int count = 0;
            while (n) {
                n &= (n - 1);
                count++;
            }
            return count;
        }

    public:
        struct ProcessorInfo {
            uint16_t cores, logicalProcessors;
        };

        struct MemoryInfo {
            uint64_t total;
            size_t file, paged, nonPaged, workingSet;
        };

        static ProcessorInfo getProcessorInfo() {
            ProcessorInfo info = { 0,0 };
            SYSTEM_LOGICAL_PROCESSOR_INFORMATION* buffer = nullptr, * ptr = nullptr;
            DWORD returnLength = 0;
            DWORD byteOffset = 0;

            DWORD rc = GetLogicalProcessorInformation(buffer, &returnLength);
            buffer = (SYSTEM_LOGICAL_PROCESSOR_INFORMATION*)ghnew uint8_t[returnLength];
            rc = GetLogicalProcessorInformation(buffer, &returnLength);

            ptr = buffer;

            while (byteOffset + sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION) <= returnLength) {
                switch (ptr->Relationship) {
                case RelationProcessorCore:
                    info.cores++;
                    info.logicalProcessors += countSetBits(ptr->ProcessorMask);
                    break;
                default:
                    break;
                }
                byteOffset += sizeof(SYSTEM_LOGICAL_PROCESSOR_INFORMATION);
                ptr++;
            }

            delete[] buffer;
            return info;
        }

        static MemoryInfo getMemoryInfo() {
            MemoryInfo info = {};

            ULONGLONG total;
            GetPhysicallyInstalledSystemMemory(&total);
            info.total = total;

            HANDLE hProcess = GetCurrentProcess();
            PROCESS_MEMORY_COUNTERS pmc;

            if (GetProcessMemoryInfo(hProcess, &pmc, sizeof(pmc))) {
                info.file = pmc.PagefileUsage;
                info.paged = pmc.QuotaPagedPoolUsage;
                info.nonPaged = pmc.QuotaNonPagedPoolUsage;
                info.workingSet = pmc.WorkingSetSize;
            }

            return info;
        }
    };
}